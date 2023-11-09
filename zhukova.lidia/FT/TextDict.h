#ifndef FT_TEXTDICT_H
#define FT_TEXTDICT_H
#include <string>
#include <map>
#include <stdexcept>
namespace zhukova
{
  struct TextNode
  {
    std::string text;
    bool isCoded = encodingName[0];
    std::string encodingName;
  };
  struct TextDict
  {
    std::map< std::string, TextNode > dict;
  };
  TextNode getTextNode(const TextDict& src, std::string& textName);
}
#endif
