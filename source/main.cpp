#include <iostream>
#include <fstream>

#include "Node.cpp"

int main(int argc, char **argv)
{
    if (argc < 3)
        return 1;

    std::ifstream ifile;
    ifile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
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
    }
    catch (std::system_error &e)
    {
        std::cerr << e.code().message() << std::endl;
        return 1;
    }
    return 0;
}
