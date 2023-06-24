#include "parser.h"
Parser::Parser(const std::string &data):
  data_(data)
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
  return res;
}
