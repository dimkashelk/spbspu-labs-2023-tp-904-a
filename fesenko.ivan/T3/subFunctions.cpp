#include "subFunctions.h"
#include <algorithm>
#include <numeric>

int mulPoint(const fesenko::Point &lhs, const fesenko::Point &rhs)
{
  return lhs.x * rhs.y;
}

double fesenko::calcArea(double in, const Polygon &rhs)
{
  std::vector< int > plusArea, minusArea;
  std::transform(rhs.points.cbegin(), --rhs.points.cend(), ++rhs.points.cbegin(), std::back_inserter(plusArea), mulPoint);
  std::transform(--rhs.points.cend(), rhs.points.cend(), rhs.points.cbegin(), std::back_inserter(plusArea), mulPoint);
  std::transform(++rhs.points.cbegin(), rhs.points.cend(), rhs.points.cbegin(), std::back_inserter(minusArea), mulPoint);
  std::transform(rhs.points.cbegin(), ++rhs.points.cbegin(), --rhs.points.cend(), std::back_inserter(minusArea), mulPoint);
  int positive = std::accumulate(plusArea.cbegin(), plusArea.cend(), 0);
  int negative = std::accumulate(minusArea.cbegin(), minusArea.cend(), 0);
  int result = std::abs(positive - negative);
  return in + (static_cast< double >(result) * 0.5);
}

bool fesenko::isOdd(const Polygon &rhs)
{
  return rhs.points.size() % 2 != 0;
}

bool fesenko::isEven(const Polygon &rhs)
{
  return !isOdd(rhs);
}

fesenko::isNumber::isNumber(size_t number):
  number_(number)
{}

bool fesenko::isNumber::operator()(const Polygon &rhs)
{
  return rhs.points.size() == number_;
}
