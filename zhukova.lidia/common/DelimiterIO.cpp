#include "DelimiterIO.h"
namespace zhukova
{
  std::istream & operator>>(std::istream & in, DelimiterIO && dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '\0';
    in >> c;
    if (in && (c != dest.value))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
}
