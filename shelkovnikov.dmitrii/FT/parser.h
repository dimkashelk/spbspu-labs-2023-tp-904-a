#ifndef FT_PARSER_H
#define FT_PARSER_H
#include <string>
class Parser
{
public:
  explicit Parser(const std::string &data);

private:
  std::string data_;
};
#endif
