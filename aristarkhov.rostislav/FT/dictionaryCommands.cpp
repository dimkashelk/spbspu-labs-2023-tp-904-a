#include "dictionaryCommands.h"

#include <string>
#include <fstream>
#include <algorithm>

namespace aristarkhov
{
  void createDictionary(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string dict_name = "";
    in >> dict_name;
    Dictionary dict;
    if (!searchDict(dictionaries, dict_name))
    {
      dictionaries.emplace(dict_name, dict);
      out << "Dictionary \"" << dict_name << "\" has been created.\n";
    }
    else
    {
      out << "Dictionary \"" << dict_name << "\" already exists.\n";
    }
  }

  void deleteDictionary(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string dict_name = "";
    in >> dict_name;

    validateDictExists(dictionaries, dict_name);

    auto place = dictionaries.find(dict_name);
    dictionaries.erase(place);
    out << "Dictionary \"" << dict_name << "\" was deleted.\n";
  }

  void readTextIntoDictionary(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string dict_name;
    in >> dict_name;

    validateDictExists(dictionaries, dict_name);

    std::string line;
    in.ignore();
    std::getline(in, line);

    const std::string delimiters = " \n\r\t,.;:!?'\"-";

    size_t start = line.find_first_not_of(delimiters);
    size_t end;

    while (start != std::string::npos)
    {
      end = line.find_first_of(delimiters, start + 1);
      if (end == std::string::npos)
      {
        end = line.length();
      }

      std::string word = line.substr(start, end - start);

      word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
      std::transform(word.begin(), word.end(), word.begin(), tolower);
      ++dictionaries[dict_name][word];

      start = line.find_first_not_of(delimiters, end + 1);
    }

    out << "Added text to dictionary \"" << dict_name << "\".\n";
  }

  void readFile(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string dict_name = "";
    in >> dict_name;

    validateDictExists(dictionaries, dict_name);

    std::string file_name = "";
    in >> file_name;
    std::ifstream file(file_name);
    if (!file.is_open())
    {
      throw std::runtime_error("File didn't open");
    }

    std::string word;
    while (file >> word)
    {
      word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
      std::transform(word.begin(), word.end(), word.begin(), tolower);
      ++dictionaries[dict_name][word];
    }

    out << "File \"" << file_name << "\" has been read into the dictionary \"" << dict_name << "\".\n";
  }

}
