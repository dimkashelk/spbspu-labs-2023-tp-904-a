#include "parser.h"
Parser::Parser(const std::string &data):
  data_(skipSpaceInBeginEnd(data))
{}
std::string Parser::operator()()
{
  std::string::size_type space = data_.find(' ');
  std::string res;
  if (space == std::string::npos)
  {
    res = data_;
    data_ = "";
  }
  else
  {
    res = data_.substr(0, space);
  }
  data_ = skipSpaceInBeginEnd(data_);
  return res;
}
std::string Parser::skipSpaceInBeginEnd(const std::string &str)
{
  const std::string spaces = " \t\n";
  const auto strBegin = str.find_first_not_of(spaces);
  if (strBegin == std::string::npos)
  {
    return "";
  }
  const auto strEnd = str.find_last_not_of(spaces);
  const auto strRange = strEnd - strBegin + 1;
  return str.substr(strBegin, strRange);
}
bool Parser::hasNext()
{
  return data_ != "";
}
