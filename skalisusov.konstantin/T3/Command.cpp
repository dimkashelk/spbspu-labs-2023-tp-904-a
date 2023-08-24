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
void skalisusov::areaEven(const std::vector<Polygon> &dest, std::ostream &out)
{
  std::vector< Polygon > evePoly;
  std::copy_if(dest.begin(), dest.end(),std::back_inserter(evePoly), isEven);
  std::vector< double > areaVector;
  std::transform(std::begin(evePoly),std::end(evePoly),std::back_inserter(areaVector), getArea);
  auto areaSum = std::accumulate(std::begin(areaVector),std::end(areaVector), 0.0);
  out << std::setprecision(1) << areaSum;
}

void skalisusov::areaOdd(const std::vector<Polygon> &dest, std::ostream &out)
{
  std::vector< Polygon > evePoly;
  std::copy_if(dest.begin(), dest.end(),std::back_inserter(evePoly), isOdd);
  std::vector< double > areaVector(evePoly.size());
  std::transform(std::begin(evePoly),std::end(evePoly),std::begin(areaVector), getArea);
  auto areaSum = std::accumulate(std::begin(areaVector),std::end(areaVector), 0.0);
  out << std::setprecision(1) << areaSum;
}
void skalisusov::areaMean(const std::vector<Polygon> &dest, std::ostream &out)
{
  if(dest.empty())
  {
    // какой то обработчик ошибок, пока что не придумал ,)
  }
  std::size_t count = dest.size();
  std::vector< double > areaVector(dest.size());
  std::transform(std::begin(dest),std::end(dest),std::begin(areaVector), getArea);
  auto areaSum = std::accumulate(std::begin(areaVector),std::end(areaVector),0.0);
  areaSum = areaSum / count;
  out << std::setprecision(1) << areaSum;
}
