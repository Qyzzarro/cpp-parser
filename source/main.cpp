#include <iostream>
#include <fstream>

#include "Node.hpp"

int main(int argc, char** argv)
{

    if (argc < 3)
        return 1;

    std::ifstream ifile;

    ifile.open(std::string(argv[1]));

    if (ifile.is_open())
    {
        std::string buffer;
        std::getline(ifile, buffer, '\000');
        ifile.close();

        std::ofstream ofile;
        ofile.open(std::string(argv[2]));
        if (ofile.is_open())
        {
            ofile << to_string(Node::parse(buffer));
            ofile.close();
        }
    }


    return 0;
}
