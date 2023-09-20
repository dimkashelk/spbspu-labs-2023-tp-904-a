#include "functions.h"
#include <istream>
#include <iterator>
#include <functional>

namespace kryuchkova
{
  bool isName(std::string & name, const ErDictionary & dict)
  {
    return dict.getName() == name;
  }
  void doCreate(const std::string & name);
  void doInsert(std::istream & in, std::map< std::string, ErDictionary > & dicts)
  {
    std::string name;
    in >> name;
    ErDictionary::word word;
    in >> word;
    ErDictionary::translations trans;
    std::string data;
    while (std::getline(in, data, ' '))
    {
      trans.push_back(data);
    }
    auto iter = dicts.find(name);
    if (iter == dicts.end())
    {
      throw std::logic_error("No such dicts with this name");
    }
    else
    {
      (*iter).second.insert(word, trans);
    }
  }

  void doSearch(std::istream & in, const ErDictionary & dict)
  {
    std::string name;
    in >> name;
    std::string word;
    in >> word;
    ErDictionary::translations res = dict.find(word);
  }
  void doDelete(std::istream & in, ErDictionary & dict);
  void fillDict(std::istream & in, ErDictionary & dict);
  void findByFirstLet(std::istream & in, ErDictionary & dict);
  void printDict(std::ostream & out, const ErDictionary & dict);
  void exportDict(std::istream & in, ErDictionary & dict);
  void unite(ErDictionary new_dict, const ErDictionary & dict1, const ErDictionary & dict2);
  void intersect(ErDictionary new_dict, const ErDictionary & dict1, const ErDictionary & dict2);
  void symSubtract(ErDictionary new_dict, const ErDictionary & dict1, const ErDictionary & dict2);
  void subtract(ErDictionary new_dict, const ErDictionary & dict1, const ErDictionary & dict2);
  void addition(const ErDictionary & dict1, const ErDictionary & dict2);

}