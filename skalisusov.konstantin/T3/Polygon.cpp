#include "Polygon.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <numeric>


bool skalisusov::operator ==(const Point &lhs, const Point &rhs)
{
  return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}
double skalisusov::getArea(const Polygon &dest)
{
  double area;
  auto getPoint = [&](Point a, Point b)
  {
    return a.x * b.y - a.y * b.x;
  };
  std::vector< int > arr(dest.polygon.size());
  std::transform(dest.polygon.begin(), --dest.polygon.end(), ++dest.polygon.begin(), std::back_inserter(arr), getPoint);
  area = std::accumulate(arr.begin(), arr.end(), 0.0);
  area += (--dest.polygon.end())->x * dest.polygon.begin()->y - dest.polygon.begin()->x * (--dest.polygon.end())->y;
  return std::abs(area * 0.5);
}
std::istream &skalisusov::operator>>(std::istream &in, Point &point)
{
  std::istream::sentry CheckSentry(in);
  if(!CheckSentry)
  {
    return in;
  }
  in >> DelimiterIO{'('} >> point.x
  >> DelimiterIO{';'} >> point.y >> DelimiterIO{')'};
  return in;
}
std::istream &skalisusov::operator>>(std::istream &in, Polygon &polygon)
{
  std::istream::sentry CheckSentry(in);
  if(!CheckSentry)
  {
    return in;
  }
  std::size_t count = 0;
  in >> count;
  if(count < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  skalisusov::Polygon input;
  std::copy_n(std::istream_iterator< Point >(in), count, std::back_inserter(input.polygon));
  if(!in)
  {
    return in;
  }
  polygon.polygon.swap(input.polygon);
  return in;
}
std::istream &skalisusov::operator>>(std::istream &in, DelimiterIO &&dest)
{
  std::istream::sentry CheckSentry(in);
  if (!CheckSentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (c != dest.delim))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
