#include "solvingCommands.h"
#include <algorithm>
#include <cmath>
#include <functional>
#include <iterator>
#include <iomanip>
#include <numeric>
#include <outputStructs.h>

namespace mashkin
{
  using namespace std::placeholders;
  using iter = std::vector< Polygon >::iterator;

  std::vector< FullArea > getFullArea(const iter& begin, const iter& end)
  {
    auto cap = std::distance(begin, end);
    std::vector< mashkin::PositiveArea > halfPA;
    std::vector< mashkin::NegativeArea > halfNA;
    std::vector< mashkin::FullArea > area;
    halfPA.reserve(cap);
    halfNA.reserve(cap);
    area.reserve(cap);
    std::transform(begin, end, std::back_inserter(halfPA), calcPositiveArea);
    std::transform(begin, end, std::back_inserter(halfNA), calcNegativeArea);
    std::transform(halfPA.begin(), halfPA.end(), halfNA.begin(), std::back_inserter(area), solveArea);
    return area;
  }

  bool isOdd(const Polygon& data)
  {
    return data.points.size() % 2;
  }

  bool isEven(const Polygon& data)
  {
    return !(isOdd(data));
  }

  XMultiY::XMultiY(const Point& first, const Point& second):
    res(first.x * second.y)
  {
  }

  XMultiY::XMultiY():
    res(0)
  {
  }

  FullArea::FullArea():
    res(0.0)
  {
  }

  FullArea FullArea::operator+(const mashkin::FullArea& rhs)
  {
    res += rhs.res;
    return *this;
  }

  XMultiY XMultiY::operator+(const XMultiY& rhs)
  {
    res += rhs.res;
    return *this;
  }

  XMultiY solveXY(const Point& lhs, const Point& rhs)
  {
    return XMultiY(lhs, rhs);
  }

  PositiveArea::PositiveArea(const Polygon& lhs)
  {
    std::transform(lhs.points.begin(), --lhs.points.end(), ++lhs.points.begin(), std::back_inserter(halfArea), solveXY);
    std::transform(--lhs.points.end(), lhs.points.end(), lhs.points.begin(), std::back_inserter(halfArea), solveXY);
  }

  PositiveArea calcPositiveArea(const Polygon& lhs)
  {
    return PositiveArea(lhs);
  }

  NegativeArea::NegativeArea(const Polygon& lhs, const Polygon& rhs)
  {
    std::transform(++lhs.points.begin(), lhs.points.end(), rhs.points.begin(), std::back_inserter(halfArea), solveXY);
    std::transform(lhs.points.begin(), ++lhs.points.begin(), --rhs.points.end(), std::back_inserter(halfArea), solveXY);
  }

  NegativeArea calcNegativeArea(const Polygon& lhs)
  {
    auto rhs = lhs;
    return NegativeArea(lhs, rhs);
  }

  FullArea::FullArea(const PositiveArea& first, const NegativeArea& second)
  {
    XMultiY positive = std::accumulate(first.halfArea.begin(), first.halfArea.end(), XMultiY());
    XMultiY negative = std::accumulate(second.halfArea.begin(), second.halfArea.end(), XMultiY());
    int almostRes = std::abs(positive.res - negative.res);
    res = static_cast< double >(almostRes) * 0.5;
  }

  FullArea solveArea(const PositiveArea& first, const NegativeArea& second)
  {
    return FullArea(first, second);
  }

  std::ostream& operator<<(std::ostream& out, const FullArea& data)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << std::fixed << std::setprecision(1) << data.res;
    return out;
  }

  bool isEqual(const Polygon& data, size_t count)
  {
    return data.points.size() == count;
  }

  bool FullArea::operator<(const mashkin::FullArea& rhs)
  {
    return res < rhs.res;
  }

  bool isEqualPoints(Polygon& lhs, Polygon& rhs)
  {
    std::sort(lhs.points.begin(), lhs.points.end());
    return lhs.points == rhs.points;
  }

  bool isRightshapes(const Angle& lhs)
  {
    if (std::find(lhs.ang.begin(), lhs.ang.end(), 0) == lhs.ang.end())
    {
      return false;
    }
    else
    {
      return true;
    }
  }

  Point getVector(const Point& first, const Point& second)
  {
    return {first.x - second.x, first.y - second.y};
  }

    Vector::Vector(const mashkin::Polygon& rhs)
  {
    std::transform(rhs.points.begin(), --rhs.points.end(), ++rhs.points.begin(), std::back_inserter(vect), getVector);
    std::transform(--rhs.points.end(), rhs.points.end(), rhs.points.begin(), std::back_inserter(vect), getVector);
  }

  int solveAngle(const Point& first, const Point& second)
  {
    return (first.x * second.x + first.y * second.y);
  }

  Angle::Angle(const mashkin::Vector& rhs)
  {
    std::transform(rhs.vect.begin(), --rhs.vect.end(), ++rhs.vect.begin(), std::back_inserter(ang), solveAngle);
    std::transform(--rhs.vect.end(), rhs.vect.end(), rhs.vect.begin(), std::back_inserter(ang), solveAngle);
  }

  Angle getAngle(const Polygon& data)
  {
    Vector vector(data);
    return Angle(vector);
  }
}
