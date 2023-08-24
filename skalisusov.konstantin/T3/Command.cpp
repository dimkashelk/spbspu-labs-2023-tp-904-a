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
void skalisusov::maxVertex(const std::vector<Polygon> &dest, std::ostream &out)
{
  if(dest.empty())
  {
    // тут должен быть обработчик ошибки
  }
  std::vector< Polygon > polgon(dest.size());
  std::copy(std::begin(dest),std::end(dest),std::begin(polgon));
  auto compare = [&](Polygon lhs, Polygon rhs)
    {return lhs.polygon.size() < rhs.polygon.size();};
  std::sort(std::begin(polgon),std::end(polgon),compare);
  auto end = polgon[polgon.size()-1];
  std::size_t maxVertex = end.polygon.size();
  out << maxVertex;
}
void skalisusov::minArea(const std::vector<Polygon> &dest, std::ostream &out)
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
  double minArea = area[0];
  out << std::setprecision(1) << minArea;
}
void skalisusov::minVertex(const std::vector<Polygon> &dest, std::ostream &out)
{
  if(dest.empty())
  {
    // тут должен быть обработчик ошибки
  }
  std::vector< Polygon > polgon(dest.size());
  std::copy(std::begin(dest),std::end(dest),std::begin(polgon));
  auto compare = [&](Polygon lhs, Polygon rhs)
  {return lhs.polygon.size() < rhs.polygon.size();};
  std::sort(std::begin(polgon),std::end(polgon),compare);
  auto min = polgon[0];
  std::size_t minVertex = min.polygon.size();
  out << minVertex;
}
void skalisusov::countEven(const std::vector<Polygon> &dest, std::ostream &out)
{
  std::vector< Polygon > polygon;
  std::copy_if(std::begin(dest),std::end(dest),std::back_inserter(polygon), isEven);
  std::size_t count = polygon.size();
  out << count;
}
void skalisusov::countOdd(const std::vector<Polygon> &dest, std::ostream &out)
{
  std::vector< Polygon > polygon;
  std::copy_if(std::begin(dest),std::end(dest),std::back_inserter(polygon), isOdd);
  std::size_t count = polygon.size();
  out << count;
}
void skalisusov::countVertex(const std::vector<Polygon> &dest, std::size_t vertex, std::ostream &out)
{
  using namespace std::placeholders;
  auto numVertex = std::bind(isNumVertex,_1,vertex);
  std::vector< Polygon > polygon;
  std::copy_if(std::begin(dest),std::end(dest),std::back_inserter(polygon),numVertex);
  std::size_t shapesThisVertex = polygon.size();
  out << shapesThisVertex;
}

void skalisusov::rects(const std::vector<Polygon> &dest, std::ostream &out)
{
  std::vector< Polygon > polygon;
  std::copy_if(std::begin(dest),std::end(dest),std::back_inserter(polygon), isRects);
  std::size_t countRects = polygon.size();
  out << countRects;
}
bool skalisusov::isRects(const skalisusov::Polygon &poly)
{
  if(poly.polygon.size() == 4)
  {
    std::vector< Point > rect(poly.polygon.size());
    std::copy(std::begin(poly.polygon),std::end(poly.polygon),std::begin(rect));
    Point a = rect[0];
    Point b = rect[1];
    Point c = rect[2];
    Point d = rect[3];
    std::size_t ab = std::sqrt(pow((b.x - a.x),2)+pow((b.y - a.y),2));
    std::size_t cd = std::sqrt(pow((d.x - c.x),2)+pow((d.y - c.y),2));
    std::size_t ac = std::sqrt(pow((c.x - a.x),2)+pow((c.y - a.y),2));
    std::size_t bd = std::sqrt(pow((d.x - b.x),2)+pow((d.y - b.y),2));
    return (ab == cd && ac == bd);
  }
  return false;
}
