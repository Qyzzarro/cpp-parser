#include "Node.hpp"

using namespace std;

int Node::idgiver = 0;

std::string to_string(Node::sptr node, int tabs)
{
    std::string str = "";

    if (node == nullptr)
        return str;
    
    for (auto i = 0; i < tabs; i++)
        str += "  ";

    if (node->isList() > 0)
    {
        std::string childrenid = "";

        for (auto& i : node->getChildren())
        {
            childrenid += std::to_string(i->getId()) + " ";
        }

        str +=
            "< id: " + std::to_string(node->getId()) + "; " +
            "parentid: " + (node->getParent() == nullptr ? "null" : std::to_string(node->getParent()->getId())) + "; " +
            "name: " + node->getName() + "; " +
            "value: " + childrenid + ">\n";
            
        for(auto& i : node->getChildren())
        {
            str += to_string(i, tabs + 1);
        }
        
        return str;
    }
    else if (node->isList() < 0)
    {
        str +=
            "< id: " + std::to_string(node->getId()) + "; " +
            "parentid: " + (node->getParent() == nullptr ? "null" : std::to_string(node->getParent()->getId())) + "; " +
            "name: " + node->getName() + "; " +
            "value: " + node->getValue() + " >\n";
        return str;
    }
    else
        throw std::logic_error("to_string:: undef node type");
}

Node::sptr Node::parse(const string& istring)
{

    map<string, string> sLexems = 
    {
        {"megalexem", "(\\\"{1}[\\w ]*\\\"{1})|([a-zA-Z_]+[a-zA-Z_0-9]*)|(=)|([{}])|(\\d+)"},
        {"varName", "([a-zA-Z_]+[a-zA-Z_0-9]*)"},
        {"varValue", "(\\\"{1}[\\w ]*\\\"{1})"},
        {"charEqual", "(=)"},
        {"charBrace", "([{}])"},
        {"digit", "(\\d+)"}
    };

    map<string, regex> rLexems;

    for(auto& i : sLexems)
        rLexems.insert(std::make_pair(i.first, regex(i.second)));


    Node::sptr root = nullptr;
    Node::sptr parent = nullptr;
    Node::sptr node = nullptr;



    auto equalTockens = 0;
    auto braceTockens = 0;


    string status = "begin";
    smatch outerMatch;
    auto tempstring = istring;
    bool error = false;
    for (smatch outerMatch; regex_search(tempstring, outerMatch, rLexems["megalexem"]);)
    {
        auto curstr = outerMatch.str();
        if (regex_match(outerMatch.str(), rLexems["digit"]))
        {
            error = true;
        }
        else if (regex_match(outerMatch.str(), rLexems["varValue"]))
        {
            if (status == "charEqual")
            {
                node->setValue(outerMatch.str());

                equalTockens--;
                status = "varValue";
            }
            else
            {
                error = true;
            }
        }
        else if (regex_match(outerMatch.str(), rLexems["varName"]))
        {
            if (status == "begin" || status == "varValue" || status == "charBrace")
            {
                node = Node::create(outerMatch.str());
                if (parent != nullptr)
                    parent->addChild(node);

                if (status == "begin")
                    root = node;

                status = "varName";
            }
            else
            {
                error = true;
            }
        }
        else if (regex_match(outerMatch.str(), rLexems["charEqual"]))
        {
            if (status == "varName")
            {
                status = "charEqual";
                equalTockens++;
            }
            else
            {
                error = true;
            }
        }
        else if (regex_match(outerMatch.str(), rLexems["charBrace"]))
        {
            if (status == "charEqual" || status == "varValue" || "charBrace")
            {
                if (outerMatch.str() == "{")
                {
                    parent = node;
                    node = nullptr;

                    equalTockens--;
                    braceTockens++;
                }
                if (outerMatch.str() == "}")
                {
                    parent = parent->getParent();
                    node = nullptr;
                    braceTockens--;
                }

                status = "charBrace";
            }
            else
            {
                error = true;
            }
        }
        else
        {
            error = true;
        }

        if (equalTockens < 0 || equalTockens > 1)
            error = true;
        if (braceTockens < 0)
            error = true;
        
        tempstring = tempstring.substr(tempstring.find_first_of(outerMatch.str()) + outerMatch.str().length());
    }

    if (error == true)
        return nullptr;
    else
        return root;
}
