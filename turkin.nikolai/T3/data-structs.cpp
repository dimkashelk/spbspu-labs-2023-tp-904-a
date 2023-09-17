#include "data-structs.hpp"

#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <iomanip>
#include <io-work.hpp>

turkin::ReturnType::ReturnType(std::size_t num):
  num_({ .uns = num }),
  type_(RType::SIZE_T)
{}

turkin::ReturnType::ReturnType(double num):
  num_({ .db = num }),
  type_(RType::DOUBLE)
{}

turkin::RType turkin::ReturnType::getType() const
{
  return type_;
}

std::size_t turkin::ReturnType::getNum() const
{
  return num_.uns;
}

double turkin::ReturnType::getDouble() const
{
  return num_.db;
}

std::ostream & turkin::operator<<(std::ostream & out, const ReturnType & rt)
{
  if (rt.getType() == RType::SIZE_T)
  {
    out << rt.getNum();
  }
  else if (rt.getType() == RType::DOUBLE)
  {
    out << std::fixed << std::setprecision(1) << rt.getDouble();
  }
  return out;
}

std::istream & turkin::operator>>(std::istream & in, Point & rhs)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterIO{ '(' } >> rhs.x >> DelimiterIO{ ';' } >> rhs.y >> DelimiterIO{ ')' };
  return in;
}

std::istream & turkin::operator>>(std::istream & in, Polygon & rhs)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Polygon input;
  std::size_t len = 0;
  in >> len;
  std::copy_n(std::istream_iterator< Point >(in), len, std::back_inserter(input.points));
  if (input.points.size() != len || input.points.size() < 3)
  {
    in.setstate(std::ios::failbit);
  }
  if (in)
  {
    rhs.points.swap(input.points);
  }
  return in;
}

bool turkin::operator==(const Point & lhs, const Point & rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool turkin::operator==(const Polygon & lhs, const Polygon & rhs)
{
  return lhs.points == rhs.points;
}
