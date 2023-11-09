#ifndef FT_COMMANDS_H
#define FT_COMMANDS_H
#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <fstream>
#include <functional>
#include "Coding.h"
#include "Encoding.h"
#include "TextDict.h"
#include "IOEncoding.h"
namespace zhukova
{
  void printAllCommands(std::istream& in, std::ostream& out);
  void loadText(TextDict& srcTexts, std::istream& in, std::ostream& out);
  void loadEncoding(EncodingDict& srcEncodings, std::istream& in, std::ostream& out);
  void getEncoding(TextDict& srcTexts, EncodingDict& srcEncoding, std::istream& in, std::ostream& out);
  void saveEncoding(EncodingDict& srcEncoding, std::istream& in, std::ostream& out);
  bool wasCoded(const std::pair< std::string, TextNode >& src, std::string encoding, bool exactEncoding);
  std::string getTextNameIfEncoding(const std::pair< std::string, TextNode >& src, bool exactEncoding);
  void codedWith(TextDict& srcTexts, EncodingDict& srcEncoding, std::istream& in, std::ostream& out);
  void code(TextDict& srcTexts, EncodingDict& srcEncoding, std::istream& in, std::ostream& out);
  void codeWith(TextDict& srcTexts, EncodingDict& srcEncoding, std::istream& in, std::ostream& out);
  void decode(TextDict& srcTexts, EncodingDict& srcEncoding, std::istream& in, std::ostream& out);
  std::string readName(NameIO& src);
  void concatText(const TextDict& srcTexts, TextNode& lhs, std::string& rhs, std::string& encodingName, bool isExactEncoding);
  void concatenate(TextDict& srcTexts, std::istream& in, std::ostream& out);
  void saveText(TextDict& srcTexts, std::istream& in, std::ostream& out);
  std::string weightFile(std::string& filename);
  void weight(std::istream& in, std::ostream& out);
  void compare(TextDict& srcTexts, EncodingDict& srcEncoding, std::istream& in, std::ostream& out);
}
#endif
