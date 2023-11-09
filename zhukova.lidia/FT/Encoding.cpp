#include "Encoding.h"
#include "IOEncoding.h"
namespace zhukova
{
  const Encoding& checkIfEncodingExists(const EncodingDict& src, const std::string& encodingName)
  {
    try
    {
      return src.dict.at(encodingName);
    }
    catch (const std::out_of_range& e)
    {
      throw std::invalid_argument("<there is no " + encodingName + " text>");
    }
  }
  bool encodingProbabilityComparator(const EncodingNode& lhs, const EncodingNode& rhs)
  {
    return (lhs.probability > rhs.probability);
  }
  bool addEncoding(EncodingDict& dest, const std::string& text, const std::string& encodingName)
  {
    Encoding newEncoding = Encoding();
    std::string tempText = text;
    std::sort(tempText.begin(), tempText.end());
    increaseProbability(newEncoding, tempText, tempText[0]);
    newEncoding.sumAmount = text.size();
    std::sort(newEncoding.list.begin(), newEncoding.list.end(), encodingProbabilityComparator);
    using namespace std::placeholders;
    getCodesOfSymbol(newEncoding, newEncoding.list.begin(), newEncoding.list.end());
    dest.dict.insert({encodingName, newEncoding});
    return false;
  }
  bool isSameSymbol(const EncodingNode& src, const char character)
  {
    return (src.symbol == character);
  }
  void increaseProbability(Encoding& listOfSymbols, std::string& text, char symbol)
  {
    using namespace std::placeholders;
    EncodingNode newChar = EncodingNode();
    newChar.symbol = symbol;
    newChar.probability = std::count(text.begin(), text.end(), symbol);
    listOfSymbols.sumAmount += newChar.probability;
    listOfSymbols.list.push_back(newChar);
    auto nextSymbol = std::find_if_not(text.begin(), text.end(), std::bind(std::equal_to< char >(), _1, symbol));
    if (text.end() == nextSymbol)
    {
      return;
    }
    increaseProbability(listOfSymbols, text.substr(nextSymbol-text.begin()), *nextSymbol);
  }
  void addBit(EncodingNode& it, bool bit)
  {
    it.code.push_back(bit);
  }
  size_t sumProbabilities(const std::vector< EncodingNode >& encoding)
  {
    std::vector< size_t > probabilities;
    using namespace std::placeholders;
    std::transform(encoding.begin(), encoding.end(), std::back_inserter(probabilities), getProbability);
    return std::accumulate(probabilities.begin(), probabilities.end(), 0);
  }
  size_t getProbability(const EncodingNode& node)
  {
    return node.probability;
  }
  void getCodesOfSymbol(Encoding& encoding,
      std::vector< EncodingNode >::iterator beginNode,
      std::vector< EncodingNode >::iterator endNode)
  {
    using namespace std::placeholders;
    if ((beginNode + 1) == endNode)
    {
      return;
    }
    if ((beginNode + 2) == endNode)
    {
      beginNode->code.push_back(false);
      (beginNode + 1)->code.push_back(true);
      return;
    }
    auto midIt = beginNode;
    std::vector< EncodingNode > left = {beginNode, midIt + 1};
    std::vector< EncodingNode > right = {midIt + 1 , endNode};
    while (sumProbabilities(left) < sumProbabilities(right))
    {
      midIt++;
      left = {beginNode, midIt + 1};
      right = {midIt + 1, endNode};
    }
    std::for_each(beginNode, midIt, std::bind(addBit, _1, false));
    std::for_each(midIt, endNode, std::bind(addBit, _1, true));
    getCodesOfSymbol(encoding, beginNode, midIt);
    getCodesOfSymbol(encoding, midIt, endNode);
  }
}
