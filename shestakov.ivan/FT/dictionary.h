#ifndef UNTITLED4_DICTIONARY_H
#define UNTITLED4_DICTIONARY_H
#include <iostream>
#include <map>

namespace shestakov
{
  struct Dictionary
  {
    std::map< std::string, size_t > dict;
  };
  using my_map = std::map< std::string, Dictionary >;
  bool searchWrd(const Dictionary &dictionaries, const std::string &word);
  size_t countFreq(const std::pair< std::string, size_t > &dictionary);
  bool compSet(const std::pair< std::string, size_t > &first, const std::pair< std::string, size_t > &second);
  bool compWord(const std::pair<std::string, size_t> &pair, const Dictionary &dictionary);
}
#endif
