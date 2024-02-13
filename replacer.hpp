#ifndef REPLACER_HPP
#define REPLACER_HPP

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <regex>

#include "lib/json/single_include/nlohmann/json.hpp"

using json = nlohmann::json;

class Replacer
{
public:
    Replacer(const std::string&, const std::string&);

private:
    void read_database(const std::string&); // file stugel, barery lcel seti ej
    void read_input(const std::string&); // file stugel, texty lcel intial texti mej
    void find_and_count_names();
    void replace_names();
    void make_json();
    void write_into_json_file();

private:
    std::string _text;
    std::unordered_map<std::string, int> _counter;
    std::unordered_set<std::string> _db;
    json _result;
};

#endif // REPLACER_HPP