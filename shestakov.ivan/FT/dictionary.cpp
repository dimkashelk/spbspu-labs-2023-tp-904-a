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
  std::pair< size_t, std::string > returnSet(const std::pair< std::string, size_t > &pair)
  {
    std::pair< size_t, std::string > ret_pair;
    ret_pair.first = pair.second;
    ret_pair.second = pair.first;
    return ret_pair;
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
