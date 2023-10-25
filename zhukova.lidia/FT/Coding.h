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
  bool isSymbol(const EncodingNode & src, char symbol);
  void addCharCode(std::string & codedText, size_t & currentByteLeft, char & codedByte, const bool & symbolCode);
  void codeChar(const Encoding & encoding,
      char symbol,
      std::string & codedText,
      size_t & currentByteLeft,
      char & codedByte);
  void codeText(TextDict & srcTexts,
      EncodingDict & srcEncodings,
      const TextNode& text,
      const std::string & codedName,
      const std::string & encodingName,
      bool newEncoding);
  void decodeText(TextDict& srcTexts,
      Encoding& encoding,
      const std::string& text,
      const std::string& decodedName);
}
#endif
