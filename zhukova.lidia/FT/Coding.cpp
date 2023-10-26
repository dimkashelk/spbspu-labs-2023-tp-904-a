#include "Coding.h"
namespace zhukova
{
  using str = std::string;
  bool isSymbol(const EncodingNode& src, char symbol)
  {
    return src.symbol == symbol;
  }
  void codeChar(const Encoding& encoding,
      char symbol,
      str& codedText,
      size_t& currentByteLeft,
      char& codedByte)
  {
    using namespace std::placeholders;
    auto symbolIt = std::find_if(encoding.list.begin(), encoding.list.end(), std::bind(isSymbol, _1, symbol));
    if (symbolIt == encoding.list.end())
    {
      throw std::invalid_argument("<ENCODING IS INCORRECT>");
    }
    auto symbolCode = symbolIt->code;
    auto addCode = std::bind(addCharCode,
        std::ref(codedText),
        std::ref(currentByteLeft),
        std::ref(codedByte),
        _1);
    std::for_each(symbolCode.begin(), symbolCode.end(), addCode);
  }
  void addCharCode(str& codedText, size_t& currentByteLeft, char& codedByte, const bool& symbolCode)
  {
    codedByte = (symbolCode ? (codedByte << 1 | (0b00000001)) : codedByte << 1);
    currentByteLeft--;
    if (currentByteLeft == 0)
    {
      codedText = codedText + codedByte;
      codedByte = 0b00000000;
      currentByteLeft = 8;
    }
  }
  void codeText(TextDict& srcT,
      EncodingDict& srcE,
      const TextNode& text,
      const str& cName,
      const str& eName,
      const bool newE)
  {
    if (newE)
    {
      addEncoding(srcE, text.text, eName);
    }
    auto encoding = checkIfEncodingExists(srcE, eName);
    str codedText;
    size_t currentByteLeft = 8;
    char codedByte = 0b00000000;
    using namespace std::placeholders;
    try
    {
      auto codeCurChar = std::bind(codeChar,
          encoding,
          _1,
          std::ref(codedText),
          std::ref(currentByteLeft),
          std::ref(codedByte));
      std::for_each(text.text.begin(), text.text.end(), codeCurChar);
      std::vector< bool > lastBits(currentByteLeft, false);
      auto addCode = std::bind(addCharCode,
          std::ref(codedText),
          std::ref(currentByteLeft),
          std::ref(codedByte),
          _1);
      std::for_each(lastBits.begin(), lastBits.end(), addCode);
    }
    catch (const std::invalid_argument& e)
    {
      throw std::invalid_argument("< " + eName + " is incorrect>");
    }
    TextNode coded = TextNode();
    coded.isCoded = 1;
    coded.encodingName = eName;
    coded.text = codedText;
    srcT.dict.insert(std::make_pair(cName, coded));
  }
  bool isBitOnPlace(const EncodingNode& node, std::vector< bool >& codedSymbol)
  {
    return (codedSymbol[codedSymbol.size() - 1] == node.code[codedSymbol.size() - 1]);
  }
  void decodeChar(const std::vector< EncodingNode >& encoding,
      std::vector< EncodingNode >::const_iterator& dest,
      str& decodedText, char symbol,
      size_t& bitNumberInSymbol,
      std::vector< bool >& codedSymbol)
  {
    using namespace std::placeholders;
    bitNumberInSymbol = 0;
    while ((bitNumberInSymbol < 8)&& (*dest).code.size() > codedSymbol.size())
    {
      bool bit = symbol& static_cast<char>(std::pow(2, 7 - bitNumberInSymbol++));
      codedSymbol.push_back(bit);
      dest = std::find_if(dest, encoding.end(), std::bind(isBitOnPlace, _1, std::ref(codedSymbol)));
      if (dest == encoding.end())
      {
        throw std::logic_error("<wrong encoding>");
      }
      if ((*dest).code.size() == codedSymbol.size())
        {
          decodedText.push_back((*dest).symbol);
          dest = encoding.begin();
          codedSymbol.clear();
        }
      }
  }
  void decodeText(TextDict& srcTexts, Encoding& encoding, const str& text, const str& decodedName)
  {
    str decodedText;
    size_t currentBitRead = 0;
    std::vector< bool > codedSymbol;
    std::vector< EncodingNode >::const_iterator& dest = encoding.list.begin();
    using namespace std::placeholders;
    try
    {
      auto decodeCurChar = std::bind(decodeChar,
          std::ref(encoding.list),
          std::ref(dest),
          std::ref(decodedText),
          _1,
          std::ref(currentBitRead),
          std::ref(codedSymbol));
      std::for_each(text.begin(), text.end(), decodeCurChar);
      TextNode newText = TextNode();
      newText.text = decodedText;
      srcTexts.dict.insert(std::make_pair(decodedName, newText));
    }
    catch (const std::logic_error& e)
    {
      std::cout << e.what();
    }
  }
}
