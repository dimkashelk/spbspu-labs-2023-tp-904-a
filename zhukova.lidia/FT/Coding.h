#ifndef FT_CODING_H
#define FT_CODING_H
#include <vector>
#include <algorithm>
#include <functional>
#include <math.h>
#include "TextDict.h"
#include "Encoding.h"
namespace zhukova
{
  using str = std::string;
  bool isSymbol(const EncodingNode& src, char symbol);
  void addCharCode(str& codedText, size_t& currentByteLeft, char& codedByte, const bool& symbolCode);
  void codeChar(const Encoding& encoding, char symbol, str& cText, size_t& curByteLeft, char& cByte);
  void codeText(TextDict& srcT, encodingDict& srcE, const TextNode& text, const str& cName, const str& eName, bool newEnco);
  void decodeText(TextDict& srcT, encoding& encoding, const str& text, const str& dcName);
}
#endif
