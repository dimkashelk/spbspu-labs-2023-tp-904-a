#ifndef UNTITLED4_COMMANDS_FOR_DICTIONARIES_H
#define UNTITLED4_COMMANDS_FOR_DICTIONARIES_H
#include <iostream>
#include <map>
#include "dictionary.h"

namespace shestakov
{
  void addDictionary(std::map< std::string, Dictionary > &dictionaries, std::istream& in, std::ostream &out);
  void searchDictionary(const std::map< std::string, Dictionary > &dictionaries, std::istream& in, std::ostream &out);
  void deleteDictionary(my_map &dictionaries, std::istream &in, std::ostream &out);
  void createIntersectionDict(my_map &dictionaries, std::istream &in, std::ostream &out);
  void countIntersection(const my_map &dictionaries, std::istream &in, std::ostream &out);
  void readFile(my_map &dictionaries, std::istream &in, std::ostream &out);
}
#endif
