#include "DelimiterIO.hpp"

#include <iomanip>
#include <bitset>
#include <algorithm>

std::istream& kabanov::operator>>(std::istream& in, kabanov::DelimiterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (c != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
