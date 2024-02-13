#include "replacer.hpp"

Replacer::Replacer(const std::string& input_filename, const std::string& db_filename)
{
    read_input(input_filename);
    read_database(db_filename);
}

void Replacer::read_database(const std::string& db_filename)
{
    std::ifstream file(db_filename);
    std::string line;

    if (!file.is_open())
    {
        throw std::ios_base::failure("Cannot open database file.");
    }

    while (std::getline(file, line)) {
        std::stringstream iss(line);
        std::string token;
        while (std::getline(iss, token, ',')) {
            token.erase(0, 1);
            token.pop_back();
            _db.insert(token);
        }
    }

    file.close();

    find_and_count_names();
}

void Replacer::read_input(const std::string& input_filename)
{
    std::ifstream file(input_filename);
    if (!file.is_open()) {
        throw std::ios_base::failure("Cannot open input file.");
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    _text = buffer.str();

    file.close();
}

void Replacer::find_and_count_names()
{

    std::regex word_regex("\\b[A-Z][a-zA-Z]*([.,;!?)]|\\b)");
    auto words_begin = std::sregex_iterator(_text.begin(), _text.end(), word_regex);
    auto words_end = std::sregex_iterator();

    for (auto it = words_begin; it != words_end; ++it)
    {
        std::string word = it->str();
        if (!std::isalpha(word.back()))
        {
            word.pop_back();
        }

        if (_db.find(word) != _db.end())
        {
            ++_counter[word];
        }
    }
    replace_names();
}

void Replacer::replace_names()
{
    for (const auto& pair : _counter) {
        std::regex nameRegex("\\b" + pair.first + "[.,;!?]*\\b");
        _text = std::regex_replace(_text, nameRegex, "X");
    }
    make_json();
}

void Replacer::make_json()
{
    _result["Text"] = _text; //_text;

    for (const auto& pair : _counter)
    {
        _result["ProperNouns"][pair.first] = pair.second;
    }
    write_into_json_file();
}

void Replacer::write_into_json_file()
{
    std::ofstream output_file("output.json");
    output_file << _result.dump(3);
}


