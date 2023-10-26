#include "Commands.h"
namespace zhukova
{
  void printAllCommands(std::istream& in, std::ostream& out)
  {
    out << "help\n";
    out << "load <text> <filename>\n";
    out << "getEncoding <encoding> <text>\n";
    out << "saveEncoding <filename> <encoding>\n";
    out << "loadEncoding <encoding> <filename>\n";
    out << "codedWith\n";
    out << "codedWith <encoding>\n";
    out << "code <text> <coded-text> <encoding>\n";
    out << "codeWith <text> <coded-text> <encoding>\n";
    out << "decode <coded-text> <text> <encoding>\n";
    out << "concat <text-1> <text-2> ... <text-n> <dest-text>\n";
    out << "concat <coded-text-1> <coded-text-2> ... <coded-text-n> <dest-text>\n";
    out << "save <filename> <text>\n";
    out << "weight <filename-1> <filename-2> ... <filename-n>\n";
    out << "compare <text> <encoding-1> <encoding-2>\n";
  }
  void loadText(TextDict& srcTexts, std::istream& in, std::ostream& out)
  {
    std::string text, filename;
    in >> std::noskipws >> DelimiterIO{' '} >> text >> DelimiterIO{' ' } >> filename >> std::skipws;
    TextNode newText = TextNode();
    if (srcTexts.dict.find(text) != srcTexts.dict.end())
    {
      throw std::invalid_argument("<encoding was already loaded>");
    }
    std::ifstream inFile;
    inFile.open(filename, std::ios::binary);
    if (!inFile.is_open())
    {
      throw std::invalid_argument("<file was not opened>");
    }
    inFile >> std::noskipws;
    using in_iter = std::istream_iterator< char >;
    std::copy(in_iter(inFile), in_iter(), std::back_inserter(newText.text));
    newText.isCoded = false;
    srcTexts.dict.insert(std::make_pair(text, newText));
    out << "text was loaded successfully\n";
  }
  void loadEncoding(EncodingDict& srcEncodings, std::istream& in, std::ostream& out)
  {
    std::string encoding, filename;
    in >> std::noskipws >> DelimiterIO{' ' } >> encoding >> DelimiterIO{' ' } >> filename >> std::skipws;
    if (srcEncodings.dict.find(encoding) != srcEncodings.dict.end())
    {
      throw std::invalid_argument("<encoding was already loaded>");
    }
    Encoding newEncoding = Encoding();
    std::ifstream inFile;
    inFile.open(filename, std::ios::binary);
    if (!inFile.is_open())
    {
      throw std::invalid_argument("<file was not opened>");
    }
    inFile >> std::noskipws >> newEncoding >> std::skipws;
    srcEncodings.dict.insert(std::make_pair(encoding, newEncoding));
    out << "encoding was loaded successfully\n";
  }

  void getEncoding(TextDict& srcTexts, EncodingDict& srcEncoding, std::istream& in, std::ostream& out)
  {
    std::string encoding, text;
    in >> encoding >> text;
    addEncoding(srcEncoding, srcTexts.dict.at(text).text, encoding);
    out << "encoding was made successfully\n";
  }
  void saveEncoding(EncodingDict& srcEncoding, std::istream& in, std::ostream& out)
  {
    std::string filename, encodingName;
    in >> filename >> encodingName;
    std::ofstream outText;
    outText.open(filename, std::ios::binary);
    auto encoding = srcEncoding.dict.find(encodingName);
    if (encoding == srcEncoding.dict.end())
    {
      throw std::invalid_argument("<wrong argument>");
    }
    outText << encoding->second;
    out << "encoding was saved successfully\n";
  }
  bool wasCoded(const std::pair< std::string, TextNode >& src, std::string encoding, bool exactEncoding)
  {
    if (src.second.isCoded)
    {
      if (!exactEncoding)
      {
        return true;
      }
      else if (src.second.encodingName == encoding)
      {
        return true;
      }
    }
  return false;
  }
  std::string getTextNameIfEncoding(const std::pair< std::string, TextNode >& src, bool exactEncoding)
  {
    if (!exactEncoding)
    {
      return src.first + " - " + src.second.encodingName;
    }
    return src.first;
  }
  void codedWith(TextDict& srcTexts, EncodingDict& srcEncoding, std::istream& in, std::ostream& out)
  {
    using namespace std::placeholders;
    in >> std::noskipws >> DelimiterIO{' '} >> std::skipws;
    if (in)
    {
      std::string encodingName;
      in >> encodingName;
      std::vector< std::string > texts;
      std::vector<std::pair< std::string, TextNode >> temp;
      auto trueWasCoded = std::bind(wasCoded, _1, encodingName, true);
      std::copy_if(srcTexts.dict.begin(), srcTexts.dict.end(), std::back_inserter(temp), trueWasCoded);
      auto getName = std::bind(getTextNameIfEncoding, _1, true);
      std::transform(temp.begin(), temp.end(), std::back_inserter(texts), getName);
    }
    else
    {
      in.clear();
      std::vector< std::string > texts;
      std::vector<std::pair< std::string, TextNode >> temp;
      auto wasNotCoded = std::bind(wasCoded, _1, "", false);
      std::copy_if(srcTexts.dict.begin(), srcTexts.dict.end(), std::back_inserter(temp), wasNotCoded);
      auto getName = std::bind(getTextNameIfEncoding, _1, false);
      std::transform(temp.begin(), temp.end(), std::back_inserter(texts), getName);
    }
    auto outIt = std::ostream_iterator< std::string >(std::cout, "\n");
    std::copy(texts.begin(), texts.end(), outIt);
  }
  void code(TextDict& srcTexts, EncodingDict& srcEncoding, std::istream& in, std::ostream& out)
  {
    std::string textName, codedTextName, encodingName;
    in >> textName >> codedTextName >> encodingName;
    TextNode text = getTextNode(srcTexts, textName);
    codeText(srcTexts, srcEncoding, text, codedTextName, encodingName, true);
    out << "text was coded successfully\n";
  }
  void codeWith(TextDict& srcTexts, EncodingDict& srcEncoding, std::istream& in, std::ostream& out)
  {
    std::string textName, codedTextName, encodingName;
    in >> textName >> codedTextName >> encodingName;
    TextNode text = getTextNode(srcTexts, textName);
    codeText(srcTexts, srcEncoding, text, codedTextName, encodingName, false);
    out << "text was coded successfully\n";
  }
  void decode(TextDict& srcTexts, EncodingDict& srcEncoding, std::istream& in, std::ostream& out)
  {
    std::string codedTextName, decodedTextName, encodingName;
    in >> codedTextName >> decodedTextName >> encodingName;
    Encoding encoding = Encoding();
    TextNode coded = TextNode();
    encoding = srcEncoding.dict.at(encodingName);
    coded = srcTexts.dict.at(codedTextName);
    if ((coded.isCoded == true)&& (coded.encodingName != encodingName))
    {
      throw std::invalid_argument("<this text was coded in another encoding>");
    }
    decodeText(srcTexts, encoding, coded.text, decodedTextName);
    out << "text was decoded successfully\n";
  }
  void concatText(const TextDict& srcTexts, TextNode& lhs, std::string& rhs, std::string& encodingName, bool isExactEncoding)
  {
    auto rhsTextNode = getTextNode(srcTexts, rhs);
    if ((rhsTextNode.encodingName == encodingName) || (!isExactEncoding))
    {
      lhs.text = lhs.text + rhsTextNode.text;
      return;
    }
  }
  std::string readName(NameIO& src)
  {
    return src.name;
  }
  void concatenate(TextDict& srcTexts, std::istream& in, std::ostream& out)
  {
    std::vector<NameIO> namesIO;
    std::vector<std::string> names;
    using in_iter = std::istream_iterator< NameIO >;
    using namespace std::placeholders;
    in >> std::noskipws;
    std::copy(in_iter(in), in_iter(), std::back_inserter(namesIO));
    in >> std::skipws;
    std::transform(namesIO.begin(), namesIO.end(), std::back_inserter(names), readName);
    in.clear();
    try
    {
      TextNode& destText = srcTexts.dict.at(names[0]);
      if (destText.isCoded)
      {
        auto concatTextToDest = std::bind(concatText,
            std::ref(srcTexts),
            std::ref(destText),
            _1,
            destText.encodingName,
            true);
      }
      else
      {
        auto concatTextToDest = std::bind(concatText,
            std::ref(srcTexts),
            std::ref(destText),
            _1,
            std::string(),
            false);
      }
      std::for_each(names.begin() + 1, names.end(), concatTextToDest);
    }
    catch (const std::runtime_error& e)
    {
    }
    catch (const std::invalid_argument& e)
    {
      std::cout << e.what();
    }
  }
  void saveText(TextDict& srcTexts, std::istream& in, std::ostream& out)
  {
    std::string filename, textName;
    in >> filename >> textName;
    std::ofstream outText;
    outText.open(filename, std::ios::binary);
    try
    {
      TextNode text = getTextNode(srcTexts, textName);
      outText << text.text;
      outText.close();
      out << "text was saved successfully\n";
    }
    catch (const std::invalid_argument& e)
    {
      outText.close();
      throw e;
    }
  }
  std::string weightFile(std::string& filename)
  {
    std::fstream file(filename);
    if (!file.is_open())
    {
      return filename + " does not exist";
    }
    size_t size = 0;
    file.seekg(0, std::ios::end);
    size = file.tellg();
    file.close();
    return filename + ' ' + std::to_string(size) + " bytes";
  };
  void weight(std::istream& in, std::ostream& out)
  {
    std::vector<NameIO> names1;
    std::vector<std::string> names;
    using in_iter = std::istream_iterator< NameIO >;
    using namespace std::placeholders;
    in >> std::noskipws;
    std::copy(in_iter(in), in_iter(), std::back_inserter(names1));
    in >> std::skipws;
    std::transform(names1.begin(), names1.end(), std::back_inserter(names), readName);
    in.clear();
    std::ostream_iterator< std::string > out_it(out, "\n");
    std::transform(names.begin(), names.end(), out_it, weightFile);
  }
  void compare(TextDict& srcTexts, EncodingDict& srcEncoding, std::istream& in, std::ostream& out)
  {
    std::string textName, encodingName1, encodingName2;
    in >> textName >> encodingName1 >> encodingName2;
    TextNode text = getTextNode(srcTexts, textName);
    Encoding encoding1 = checkIfEncodingExists(srcEncoding, encodingName1);
    Encoding encoding2 = checkIfEncodingExists(srcEncoding, encodingName2);
    std::string textName1, textName2;
    textName1 = textName + "1";
    textName2 = textName + "2";
    codeText(srcTexts, srcEncoding, text, textName1, encodingName1, false);
    codeText(srcTexts, srcEncoding, text, textName2, encodingName2, false);
    TextNode text1 = getTextNode(srcTexts, textName1);
    TextNode text2 = getTextNode(srcTexts, textName2);
    if (text1.text.size() < text2.text.size())
    {
      out << encodingName1;
    }
    else
    {
      out << encodingName2;
    }
    out << " is more effective\n";
  }
}
