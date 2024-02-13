#include "replacer.hpp"

int main()
{
    std::string input_filename = "input.txt";
    std::string db_filename = "db.txt";

    try
    {
        Replacer replacer {input_filename, db_filename};
    }
    catch (std::ios_base::failure& f)
    {
        std::cout << f.what() << std::endl;
    }

    return 0;
}