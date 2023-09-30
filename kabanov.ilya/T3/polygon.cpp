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

double kabanov::getArea(const Polygon& pol)
{
  const std::vector< Point >& points = pol.points;
  const size_t& n = points.size();

  if (n < 3)
  {
    return 0.0;
  }

  double area = 0.0;

  Polygon temp;
  for (size_t i = 0; i < n - 2; i += 2)
  {
    area += getTriangleArea(points[i], points[i + 1], points[i + 2]);
    temp.points.push_back(points[i]);
  }

  if (isEven(pol))
  {
    area += getTriangleArea(points[n - 2], points[n - 1], points[0]);
    temp.points.push_back(points[n - 2]);
  }
  else
  {
    temp.points.push_back(points[n - 1]);
  }

  area += getArea(temp);

  return area;
}
