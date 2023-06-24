#ifndef FT_PARSER_H
#define FT_PARSER_H
#include <string>
class Parser
{
public:
  explicit Parser(const std::string &data);
  std::string operator()();
private:
  std::string data_;
  std::string skipSpaceInBeginEnd(const std::string &str);
};
#endif
