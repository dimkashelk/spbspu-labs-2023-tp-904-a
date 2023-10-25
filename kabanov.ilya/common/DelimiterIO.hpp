#ifndef DELIMETERIO_HPP
#define DELIMETERIO_HPP

#include <string>

namespace kabanov
{
  struct DelimiterIO
  {
    char exp;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
}
#endif
