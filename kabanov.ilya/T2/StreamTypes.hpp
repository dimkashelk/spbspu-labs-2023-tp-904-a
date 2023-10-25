#ifndef STREAMTYPES_HPP
#define STREAMTYPES_HPP

#include <string>

namespace kabanov
{
  struct LabelIO
  {
    std::string exp;
  };

  struct LiteralIO
  {
    std::string exp;
  };

  struct CharIO
  {
    char& ref;
  };

  struct StringIO
  {
    std::string& ref;
  };

  struct ULongLongBinI
  {
    unsigned long long& ref;
  };

  struct ULongLongBinO
  {
    unsigned long long val;
  };

  std::istream& operator>>(std::istream& in, LabelIO&& dest);
  std::istream& operator>>(std::istream& in, LiteralIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, CharIO&& dest);
  std::istream& operator>>(std::istream& in, ULongLongBinI&& dest);
  std::ostream& operator<<(std::ostream& out, ULongLongBinO&& dest);
}
#endif
