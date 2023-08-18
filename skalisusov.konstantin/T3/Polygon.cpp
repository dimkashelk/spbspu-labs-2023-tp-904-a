#include "Polygon.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <numeric>


bool skalisusov::operator ==(const Point &lhs, const Point &rhs)
{
  return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}
double skalisusov::getArea(const Polygon &polygon)
{
  double sumX = 0.0;
  double sumY = 0.0;
  std::vector< int > x;
  std::vector< int > y;
  auto returPointX = [&](Point point){return point.x;};
  auto returPointY = [&](Point point){return point.y;};
  std::transform(polygon.polygon.begin(), polygon.polygon.end(),
                 std::back_inserter(x), returPointX);
  std::transform(polygon.polygon.begin(), polygon.polygon.end(),
                 std::back_inserter(y), returPointY);
  sumX = std::inner_product(x.begin(),x.end()-1,y.begin()+1, 0.0)
    + polygon.polygon.end()--->x * polygon.polygon.begin()->y;
  sumY = std::inner_product(y.begin(),y.end()-1,x.begin()+1, 0.0)
         + polygon.polygon.end()--->y * polygon.polygon.begin()->x;
  return 0.5 * std::abs(sumX - sumY);
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
  skalisusov::Polygon polygo;
  std::copy_n(std::istream_iterator< Point >(in), count, std::back_inserter(polygo.polygon));
  if(in)
  {
    polygon = polygo;
  }
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
