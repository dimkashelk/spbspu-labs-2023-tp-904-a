#include "Command.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cmath>

bool skalisusov::isNumVertex(const skalisusov::Polygon &polygon, std::size_t count)
{
  return (polygon.polygon.size() == count);
}
bool skalisusov::isEven(const skalisusov::Polygon &poly)
{
  return (poly.polygon.size() % 2 == 0);
}
bool skalisusov::isOdd(const skalisusov::Polygon &poly)
{
  return (poly.polygon.size() % 2 != 0);
}
