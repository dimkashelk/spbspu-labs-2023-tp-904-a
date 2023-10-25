#include "point.hpp"

#include <istream>
#include <DelimiterIO>

std::istream& kabanov::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterIO{'('};
  in >> point.x;
  in >> DelimiterIO{';'};
  in >> point.y;
  in >> DelimiterIO{')'};
  return in;
}
