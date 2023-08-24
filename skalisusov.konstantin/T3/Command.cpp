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
void skalisusov::areaNumOfVertex(const std::vector< Polygon > &dest, std::size_t vertex, std::ostream &out)
{
  if( vertex < 3)
  {
    throw std::invalid_argument("Invalied parameter");
  }
  std::vector< Polygon > polygonOfVertex;
  using namespace std::placeholders;
  auto redactor = std::bind(isNumVertex, _1 , vertex);
  std::copy_if(std::begin(dest),std::end(dest),std::back_inserter(polygonOfVertex),redactor);
  std::vector< double > areaShapes(polygonOfVertex.size());
  std::transform(std::begin(polygonOfVertex),std::end(polygonOfVertex),std::begin(areaShapes), getArea);
  auto areaSum = std::accumulate(std::begin(areaShapes),std::end(areaShapes),0.0);
  out << std::setprecision(1) << areaSum;
}
void skalisusov::maxArea(const std::vector<Polygon> &dest, std::ostream &out)
{
  if(dest.empty())
  {
    // тут должен быть обработчик ошибки
  }
  std::vector< Polygon > polygon(dest.size());
  std::copy(std::begin(dest),std::end(dest),std::begin(polygon));
  std::vector< double > area(polygon.size());
  std::transform(std::begin(polygon),std::end(polygon),std::begin(area), getArea);
  auto compar = [&](double a, double b){return a < b;};
  std::sort(std::begin(area),std::end(area),compar);
  double maxArea = area[area.size() - 1];
  out << std::setprecision(1) << maxArea;
}
