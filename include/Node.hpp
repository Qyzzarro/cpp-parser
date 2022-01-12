#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <map>
#include <memory>
#include <list>
#include <string>
#include <regex>

class Node
{
public:
    typedef std::shared_ptr<Node> sptr;
    typedef std::weak_ptr<Node> wptr;

    ~Node()
    {
        //std::cout << "del" << std::endl;
    }

    static Node::sptr create(const std::string& name)
    {
        auto ptr = Node::sptr(new Node(name));
        ptr->_self = ptr;
        return ptr;
    }

    static Node::sptr parse(const std::string& inputStr);

    Node::sptr getPtr(void)
    {
        return this->_self.lock();
    }

    std::list<Node::sptr> getChildren(void)
    {
        if (this->isList() > 0)
            return this->_children;
        else
            throw std::logic_error("addChild::isList() <= 0");
    }

    void addChild(Node::sptr child)
    {
        if (this->isList() == 0)
            this->_isList = 1;
        if (this->isList() > 0)
        {
            child->setParent(this->_self.lock());
            this->_children.push_back(child);
        }
        else
            throw std::logic_error("addChild::isList() < 0");
    }

    //0 - undefined, 1 - it is list, -1 - it is not
    int isList(void) const
    {
        return this->_isList;
    }

    void setValue(const std::string& value)
    {
        if (this->isList() == 0)
            this->_isList = -1;
        if (this->isList() < 0)
            this->_value = value;
        else
            throw std::logic_error("setValue:: isList() > 0");
    }

    const std::string& getValue(void) const
    {
        if (this->isList() <= 0)
            return this->_value;
        else
            throw std::logic_error("setValue:: isList() > 0");
    }

    void setParent(const Node::sptr& newParent)
    {
        this->_parent = newParent;
    } 

    Node::sptr getParent(void)
    {
        return this->_parent.lock();
    }

    int getId(void) const 
    {
        return this->_id;
    }

    const std::string& getName(void) const
    {
        return this->_name;
    }

protected:
    Node(const std::string& name) :
        _id(idgiver++),
        _value(""),
        _name(name),
        _isList(0)
    {}
private:
    static int idgiver;

    const int _id;
    //0 - undefined, 1 - it is list, -1 - it is not
    int _isList;
    wptr _parent;
    wptr _self;
    std::list<Node::sptr> _children;
    std::string _value;
    const std::string _name;
};


std::string to_string(Node::sptr node, int tabs = 0);

#endif
