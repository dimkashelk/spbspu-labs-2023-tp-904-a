#include "commands_for_dictionaries.h"
#include <algorithm>
#include <fstream>
#include <functional>
#include "auxiliary_commands.h"

namespace shestakov
{
  void addDictionary(my_map &dictionaries, std::istream &in, std::ostream &out)
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
  void searchDictionary(const my_map &dictionaries, std::istream& in, std::ostream &out)
  {
    std::string dict_name = "";
    in >> dict_name;
    if (searchDict(dictionaries, dict_name))
    {
      out << "Dictionary \"" << dict_name << "\" exist.\n";
    }
    else
    {
      out << "Dictionary \"" << dict_name << "\" does not exist.\n";
    }
  }
  void deleteDictionary(my_map &dictionaries, std::istream &in, std::ostream &out)
  {
    std::string dict_name = "";
    in >> dict_name;
    if (!searchDict(dictionaries, dict_name))
    {
      out << "Dictionary \"" << dict_name << "\" does not exist.\n";
      return;
    }
    auto place = dictionaries.find(dict_name);
    dictionaries.erase(place);
    out << "Dictionary \"" << dict_name << "\" was deleted.\n";
  }
  void createIntersectionDict(my_map &dictionaries, std::istream &in, std::ostream &out)
  {
    std::string name_1 = "";
    std::string name_2 = "";
    std::string new_name = "";
    in >> name_1 >> name_2 >> new_name;
    if (!searchDict(dictionaries, name_1) || !searchDict(dictionaries, name_2) || searchDict(dictionaries, new_name) || name_1 == name_2)
    {
      out << "Invalid argument\n";
      skipUntilNewLine(in);
      return;
    }
    using namespace std::placeholders;
    auto compWrd = std::bind(compWord, _1, dictionaries[name_2]);
    Dictionary new_d;
    const Dictionary &dict_1 = dictionaries.at(name_1);
    std::copy_if(dict_1.dict.cbegin(), dict_1.dict.cend(), std::inserter(new_d.dict, new_d.dict.begin()), compWrd);
    dictionaries.emplace(new_name, new_d);
    out << "Dictionary of intersections \"" << new_name << "\" has been created.\n";
  }
  void countIntersection(const my_map &dictionaries, std::istream &in, std::ostream &out)
  {
    using namespace std::placeholders;
    std::string name_1 = "";
    std::string name_2 = "";
    in >> name_1 >> name_2;
    if (!searchDict(dictionaries, name_1) || !searchDict(dictionaries, name_2) || name_1 == name_2)
    {
      throw std::logic_error("Invalid arguments");
    }
    const Dictionary &dict_1 = dictionaries.at(name_1);
    const Dictionary &dict_2 = dictionaries.at(name_2);
    auto compWrd = std::bind(compWord, _1, dict_2);
    size_t inter = std::count_if(dict_1.dict.cbegin(), dict_1.dict.cend(), compWrd);
    out << "Count of intersections in dictionaries \"" << name_1 << "\" and \"" << name_2 << "\" is " << inter << ".\n";
  }
  void readFile(my_map &dictionaries, std::istream &in, std::ostream &out)
  {
    std::string dict_name = "";
    in >> dict_name;
    if (!searchDict(dictionaries, dict_name))
    {
      throw std::logic_error("Dictionary does not exist");
    }
    std::string file_name = "";
    std::string word = "";
    out << "Enter file name:\n";
    in >> file_name;
    if (file_name.empty())
    {
      throw std::invalid_argument("File does not exist");
    }
    std::ifstream file(file_name);
    if (!file.is_open())
    {
      throw std::runtime_error("File didn't open");
    }
    Dictionary &dict = dictionaries.at(dict_name);
    while(!file.eof())
    {
      file >> word;
      word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
      std::transform(word.begin(), word.end(), word.begin(), ::tolower);
      if (searchWrd(dict, word))
      {
        ++dict.dict[word];
        continue;
      }
      dict.dict[word] = 1;
    }
    file.close();
    dictionaries.emplace(dict_name, dict);
    out << "File is written in the dictionary \"" << dict_name << "\".\n";
  }
}
