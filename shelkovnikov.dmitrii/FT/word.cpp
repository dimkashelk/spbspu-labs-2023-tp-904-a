#include "word.h"
#include <algorithm>
namespace
{
  char toLower(char c)
  {
    return static_cast< char >(std::tolower(c));
  }
  std::string toLowerString(const std::string &str)
  {
    std::string newStr;
    std::transform(str.begin(), str.end(), newStr.begin(), toLower);
    return newStr;
  }
}
dimkashelk::Word::Word(const std::string &data):
  data_(toLowerString(data))
{}
bool dimkashelk::Word::operator<(const dimkashelk::Word &rhs) const
{
  return data_ < rhs.data_;
}
