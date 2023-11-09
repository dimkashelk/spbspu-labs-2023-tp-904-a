#include "dictionary.h"

namespace shestakov
{
  bool searchWrd(const Dictionary &dictionary, const std::string &word)
  {
    return dictionary.dict.find(word) != dictionary.dict.end();
  }
  size_t countFreq(const std::pair< std::string, size_t > &pair)
  {
    return pair.second;
  }
  bool compSet(const std::pair< std::string, size_t > &first, const std::pair< std::string, size_t > &second)
  {
    return first.second < second.second;
  }
  bool compWord(const std::pair< std::string, size_t > &pair, const Dictionary &dictionary)
  {
    return dictionary.dict.find(pair.first) != dictionary.dict.end();
  }
}
