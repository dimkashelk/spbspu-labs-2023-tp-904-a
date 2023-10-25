#ifndef TYPESIO_H
#define TYPESIO_H

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
