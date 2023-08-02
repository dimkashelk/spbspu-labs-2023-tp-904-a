#include "polygon.hpp"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <cmath>
#include <iostructures.hpp>
std::istream & litvin::operator>>(std::istream & in, Polygon & dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t num_of_points = 0;
  in >> num_of_points;
  if (num_of_points < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  dest.points.clear();
  dest.points.reserve(num_of_points);
  std::istream_iterator< Point > point_iter(in);
  std::istream_iterator< Point > end_point_iter;
  std::copy(point_iter, end_point_iter, dest.points.begin());
  if (dest.points.size() != num_of_points)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::istream & litvin::operator>>(std::istream & in, Point & dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterIO{'('} >> dest.x >> DelimiterIO{';'} >> dest.y >> DelimiterIO{')'};
  return in;
}
size_t litvin::size(const Polygon & dest)
{
  return dest.points.size();
}
int calculate(const litvin::Point & p1, const litvin::Point & p2)
{
  return p1.x * p2.y - p1.y * p2.x;
}
double litvin::calcArea(const Polygon & pol)
{
  std::vector< int > area(size(pol));
  std::transform(pol.points.cbegin(), --pol.points.cend(), ++pol.points.cbegin(), std::back_inserter(area), calculate);
  Point first = pol.points.front();
  Point last = pol.points.back();
  area.push_back(calculate(last, first));
  double res = std::accumulate(area.cbegin(), area.cend(), 0);
  return std::abs(res) / 2;
}
double litvin::calcAreaIf(const Polygon & pol, bool (* predicate)(const Polygon & pol))
{
  return (predicate(pol)) ? calcArea(pol) : 0.0;
}
