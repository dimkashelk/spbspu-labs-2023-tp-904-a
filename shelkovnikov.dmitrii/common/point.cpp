#include "point.h"
#include "io.h"
double dimkashelk::AreaStorage::operator()(const Point &lnr, const Point &rnl)
{
  return lnr.x * rnl.y - rnl.x * lnr.y;
}
std::istream &dimkashelk::operator>>(std::istream &in, Point &point)
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
