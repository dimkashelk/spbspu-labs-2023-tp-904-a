#include "TextDict.h"
namespace zhukova
{
  TextNode getTextNode(const TextDict & src, std::string & textName)
  {
    try
    {
      return src.dict.at(textName);
    }
    catch (const std::out_of_range & e)
    {
      throw std::invalid_argument("<there is no " + textName + " text>");
    }
  }
}
