#include "polygon.hpp"

#include <algorithm>
#include <numeric>
#include <limits>
#include <istream>
#include <string>
#include <iterator>

#include "commands.hpp"

std::istream& kabanov::operator>>(std::istream& in, Polygon& pol)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t count = 0;
  in >> count;
  if (count < 3)
  {
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    in.setstate(std::ios::failbit);
    return in;
  }
  pol.points.clear();
  std::copy_n(std::istream_iterator< Point >(in), count, std::back_inserter(pol.points));
  if (!in)
  {
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    return in;
  }
  std::string whitespaces;
  std::getline(in, whitespaces);
  if (whitespaces.find_first_not_of(' ') != std::string::npos)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  return in;
}
