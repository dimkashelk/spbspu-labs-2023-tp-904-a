#include "Polygon.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
bool skalisusov::operator ==(const skalisusov::Polygon &lhs, const skalisusov::Polygon &rhs)
{
  return std::equal(lhs.shape.begin(), lhs.shape.end(), rhs.shape.begin());
}
bool skalisusov::operator ==(const Point &lhs, const Point &rhs)
{
  return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}
bool skalisusov::comparator(const skalisusov::Polygon &lhs, const skalisusov::Polygon &rhs)
{
  return (lhs.shape.size() < rhs.shape.size());
}
int getPoint(const skalisusov::Point &rhs, const skalisusov::Point &lhs)
{
  return rhs.x * lhs.y - rhs.y * lhs.x;
};
double skalisusov::getArea(const Polygon &dest)
{
  double area = 0.0;
  std::vector< int > arr(dest.shape.size());
  std::transform(dest.shape.begin(), --dest.shape.end(), ++dest.shape.begin(),
    std::back_inserter(arr), getPoint);
  area = std::accumulate(arr.begin(), arr.end(), 0.0);
  area += ( dest.shape.back()).x * dest.shape.front().y - dest.shape.front().x * (dest.shape.back()).y;
  return std::abs(area * 0.5);
}
std::istream &skalisusov::operator>>(std::istream &in, Point &point)
{
  std::istream::sentry CheckSentry(in);
  if (!CheckSentry)
  {
    return in;
  }
  in >> DelimiterIO{ '(' } >> point.x >> DelimiterIO{ ';' } >> point.y >> DelimiterIO{ ')' };
  return in;
}
std::istream &skalisusov::operator>>(std::istream &in, Polygon &rhs)
{
  std::istream::sentry CheckSentry(in);
  if (!CheckSentry)
  {
    return in;
  }
  size_t count = 0;
  in >> count;
  if (count < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > input;
  std::copy_n(std::istream_iterator< Point >(in), count, std::back_inserter(input));
  if (!in)
  {
    return in;
  }
  rhs.shape = input;
  return in;
}
