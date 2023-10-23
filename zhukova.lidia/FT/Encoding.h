#ifndef FT_ENCODING_H
#define FT_ENCODING_H
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
namespace zhukova
{
  struct EncodingNode
  {
    char symbol = '\0';
    size_t probability = 0;
    std::vector< bool > code;
  }
  struct Encoding
  {
    std::vector< EncodingNode > list;
    size_t sumAmount = 0;
  }
  struct EncodingDict
  {
    std::map< std::string, Encoding > dict;
  }
  const Encoding& checkIfEncodingExists(const EncodingDict& src, const std::string& encodingName);
  bool encodingProbabilityComparator(const EncodingNode& lhs, const EncodingNode& rhs);
  bool isSameSymbol(const EncodingNode& src, const char& character);
  bool encodingProbabilityComparator(const EncodingNode & lhs, const EncodingNode & rhs);
  void increaseProbability(Encoding& listOfSymbols, std::string& text, char symbol);
  bool addEncoding(EncodingDict & dest, const std::string & text, const std::string & encodingName);
  void addBit(EncodingNode & it, bool bit);
  size_t sumProbabilities(const std::vector< EncodingNode >& encoding);
  size_t getProbability(const EncodingNode& node);
  void getCodesOfSymbol(Encoding& encoding, std::vector< EncodingNode >::iterator beginNode, std::vector< EncodingNode >::iterator endNode);
}
#endif
