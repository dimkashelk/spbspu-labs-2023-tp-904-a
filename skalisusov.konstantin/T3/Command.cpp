#include "Command.hpp"
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <vector>
bool skalisusov::isNumVertex(const skalisusov::Polygon &rhs, size_t count)
{
  return (rhs.shape.size() == count);
}
bool skalisusov::isEven(const skalisusov::Polygon &rhs)
{
  return (rhs.shape.size() % 2 == 0);
}
bool skalisusov::isOdd(const skalisusov::Polygon &rhs)
{
  return (rhs.shape.size() % 2 != 0);
}
void skalisusov::errorMessage(std::ostream &out)
{
  iofmtguard iofmtguard(out);
  out << "<INVALID COMMAND>";
}
void skalisusov::outArea(std::ostream &out, double area)
{
  out << std::scientific << std::fixed << std::setprecision(1) << area << '\n';
}
void skalisusov::areaEven(const std::vector<Polygon> &rhs, std::ostream &out)
{
  std::vector< Polygon > evePoly;
  std::copy_if(std::begin(rhs), std::end(rhs), std::back_inserter(evePoly), isEven);
  std::vector< double > areaVector(evePoly.size());
  std::transform(std::begin(evePoly), std::end(evePoly), std::begin(areaVector), getArea);
  auto areaSum = std::accumulate(std::begin(areaVector), std::end(areaVector), 0.0);
  iofmtguard iofmtguard(out);
  outArea(out, areaSum);
}

void skalisusov::areaOdd(const std::vector<Polygon> &rhs, std::ostream &out)
{
  std::vector< Polygon > evePoly;
  std::copy_if(std::begin(rhs), std::end(rhs), std::back_inserter(evePoly), isOdd);
  std::vector< double > areaVector(evePoly.size());
  std::transform(std::begin(evePoly),std::end(evePoly), std::begin(areaVector), getArea);
  auto areaSum = std::accumulate(std::begin(areaVector), std::end(areaVector), 0.0);
  iofmtguard iofmtguard(out);
  outArea(out, areaSum);
}
void skalisusov::areaMean(const std::vector< Polygon > &rhs, std::ostream &out)
{
  if (rhs.empty())
  {
    throw std::logic_error("Polygon is empty");
  }
  size_t count = 0;
  count = rhs.size();
  std::vector< double > areaVector(rhs.size());
  std::transform(std::begin(rhs), std::end(rhs), std::begin(areaVector), getArea);
  auto areaSum = std::accumulate(std::begin(areaVector), std::end(areaVector), 0.0);
  iofmtguard iofmtguard(out);
  areaSum = areaSum / count;
  outArea(out, areaSum);
}
void skalisusov::areaNumOfVertex(const std::vector< Polygon > &rhs, size_t vertex, std::ostream &out)
{
  if (vertex < 3)
  {
    throw std::logic_error("Invalied parameter");
  }
  std::vector< Polygon > polygonOfVertex;
  using namespace std::placeholders;
  auto redactor = std::bind(isNumVertex, _1 , vertex);
  std::copy_if(std::begin(rhs),std::end(rhs), std::back_inserter(polygonOfVertex), redactor);
  std::vector< double > areaShapes(polygonOfVertex.size());
  std::transform(std::begin(polygonOfVertex), std::end(polygonOfVertex),
                 std::begin(areaShapes), getArea);
  auto areaSum = std::accumulate(std::begin(areaShapes), std::end(areaShapes), 0.0);
  iofmtguard iofmtguard(out);
  outArea(out, areaSum);
}
void skalisusov::maxArea(const std::vector<Polygon> &rhs, std::ostream &out)
{
  if (rhs.empty())
  {
    throw std::logic_error("Polygon is empty");
  }
  std::vector< Polygon > polygon(rhs.size());
  std::copy(std::begin(rhs), std::end(rhs), std::begin(polygon));
  std::vector< double > area(polygon.size());
  std::transform(std::begin(polygon), std::end(polygon), std::begin(area), getArea);
  std::sort(std::begin(area), std::end(area));
  double maxArea = 0.0;
  maxArea = area[area.size() - 1];
  iofmtguard iofmtguard(out);
  outArea(out, maxArea);
}
void skalisusov::maxVertex(const std::vector< Polygon > &rhs, std::ostream &out)
{
  if (rhs.empty())
  {
    throw std::logic_error("Polygon is empty");
  }
  std::vector< Polygon > polgon(rhs.size());
  std::copy(std::begin(rhs), std::end(rhs), std::begin(polgon));
  std::sort(std::begin(polgon), std::end(polgon), comparator);
  auto end = polgon[polgon.size()-1];
  size_t maxVertex = end.shape.size();
  iofmtguard iofmtguard(out);
  out << maxVertex << '\n';
}
void skalisusov::minArea(const std::vector< Polygon > &rhs, std::ostream &out)
{
  if (rhs.empty())
  {
    throw std::logic_error("Polygon is empty");
  }
  std::vector< Polygon > polygon(rhs.size());
  std::copy(std::begin(rhs), std::end(rhs), std::begin(polygon));
  std::vector< double > area(polygon.size());
  std::transform(std::begin(polygon), std::end(polygon), std::begin(area), getArea);
  std::sort(std::begin(area), std::end(area));
  double minArea = 0.0;
  minArea = area[0];
  iofmtguard iofmtguard(out);
  outArea(out, minArea);
}
void skalisusov::minVertex(const std::vector<Polygon> &rhs, std::ostream &out)
{
  if (rhs.empty())
  {
    throw std::logic_error("Polygon is empty");
  }
  std::vector< Polygon > polgon(rhs.size());
  std::copy(std::begin(rhs), std::end(rhs), std::begin(polgon));
  std::sort(std::begin(polgon), std::end(polgon), comparator);
  auto min = polgon[0];
  std::size_t minVertex = 0;
  minVertex = min.shape.size();
  iofmtguard iofmtguard(out);
  out << minVertex << '\n';
}
void skalisusov::countEven(const std::vector <Polygon > &rhs, std::ostream &out)
{
  std::vector< Polygon > polygon;
  std::copy_if(std::begin(rhs),std::end(rhs), std::back_inserter(polygon), isEven);
  size_t count = 0;
  count = polygon.size();
  out << count << '\n';
}
void skalisusov::countOdd(const std::vector< Polygon > &rhs, std::ostream &out)
{
  std::vector< Polygon > polygon;
  std::copy_if(std::begin(rhs), std::end(rhs), std::back_inserter(polygon), isOdd);
  size_t count = 0;
  count = polygon.size();
  iofmtguard iofmtguard(out);
  out << count << '\n';
}
void skalisusov::countVertex(const std::vector< Polygon > &rhs, size_t vertex, std::ostream &out)
{
  using namespace std::placeholders;
  if (vertex < 3)
  {
    throw std::logic_error("");
  }
  auto numVertex = std::bind(isNumVertex,_1,vertex);
  std::vector< Polygon > polygon;
  std::copy_if(std::begin(rhs), std::end(rhs), std::back_inserter(polygon), numVertex);
  size_t shapesThisVertex = 0;
  shapesThisVertex = polygon.size();
  iofmtguard iofmtguard(out);
  out << shapesThisVertex << '\n';
}
void skalisusov::rects(const std::vector<Polygon> &rhs, std::ostream &out)
{
  std::vector< Polygon > polygon;
  if (rhs.empty())
  {
    throw std::logic_error("empty");
  }
  std::copy_if(std::begin(rhs), std::end(rhs), std::back_inserter(polygon), isRects);
  size_t countRects = 0;
  countRects = polygon.size();
  iofmtguard iofmtguard(out);
  out << countRects << '\n';
}
bool skalisusov::isRects(const Polygon &rhs)
{
  if (rhs.shape.size() == 4)
  {
    std::vector< Point > rect(rhs.shape.size());
    std::copy(std::begin(rhs.shape), std::end(rhs.shape), std::begin(rect));
    Point a = rect[0];
    Point b = rect[1];
    Point c = rect[2];
    Point d = rect[3];
    size_t ab = std::sqrt(pow((b.x - a.x),2) + pow((b.y - a.y),2));
    size_t cd = std::sqrt(pow((d.x - c.x),2) + pow((d.y - c.y),2));
    size_t ac = std::sqrt(pow((c.x - a.x),2) + pow((c.y - a.y),2));
    size_t bd = std::sqrt(pow((d.x - b.x),2) + pow((d.y - b.y),2));
    return (ab == cd && ac == bd);
  }
  return false;
}
void skalisusov::rmecho(std::vector< Polygon > &rhs, std::istream &in, std::ostream &out)
{
  Polygon shape;
  in >> shape;
  if (shape.shape.size() < 3)
  {
    throw std::logic_error("Invalid parameters");
  }
  size_t count = 0;
  count = rmecho(rhs, shape);
  iofmtguard iofmtguard(out);
  out << count;
}
size_t skalisusov::rmecho(std::vector< Polygon > &rhs, Polygon &lhs)
{
  size_t count = 0;
  std::vector< Polygon > data(rhs.size());
  std::copy(std::begin(rhs), std::end(rhs), std::begin(data));
  auto it_1 = std::adjacent_find(data.begin(),data.end());
  while (it_1 != data.end())
  {
    auto next = std::adjacent_find(it_1++,data.end());
    if (next != data.end() && next->shape == it_1->shape && next->shape == lhs.shape)
    {
      data.erase(it_1,next+1);
      count++;
    }
    else
    {
      it_1 = next;
    }
  }
  rhs = data;
  return count;
}

skalisusov::Command::Command()
{
  const_area.insert({"AREA EVEN", areaEven});
  const_area.insert({"AREA ODD", areaOdd});
  const_area.insert({"AREA MEAN", areaMean});
  const_area.insert({"MAX AREA", maxArea});
  const_area.insert({"MAX VERTEXES", maxVertex});
  const_area.insert({"MIN AREA", minArea});
  const_area.insert({"MIN VERTEXES", minVertex});
  const_area.insert({"COUNT EVEN", countEven});
  const_area.insert({"COUNT ODD", countOdd});
  const_area.insert({"RECTS", rects});
  const_ver.insert({"AREA NUM", areaNumOfVertex});
  const_ver.insert({"COUNT NUM", countVertex});
  area.insert({"RMECHO", rmecho});
}
void skalisusov::Command::CommandPolygon(std::istream &in, std::ostream &out, std::vector<Polygon> &rhs,
                                         std::string &command)
{
  using namespace std::placeholders;
  try
  {
    auto polygon = std::bind(area.at(command), _1, std::ref(in), std::ref(out));
    polygon(rhs);
    return;
  }
  catch (const std::out_of_range & e)
  {}
  try
  {
    auto polygon = std::bind(const_area.at(command), _1, std::ref(out));
    polygon(rhs);
    return;
  }
  catch (const std::out_of_range & e)
  {}
  std::size_t space = command.find(' ');
  std::size_t num = std::stoull(command.substr(space));
  auto vertexes = std::bind(const_ver.at(command.substr(0, space) + " NUM"), _1, num, std::ref(out));
  vertexes(rhs);
}
std::string skalisusov::Command::listenCommand(std::istream &in)
{
  std::string comand = "0";
  in >> comand;
  if (in.eof())
  {
    throw std::runtime_error("eof");
  }
  if (comand == "RECTS" || comand == "RMECHO")
  {
    return comand;
  }
  std::string param = "0";
  in >> param;
  if (!in)
  {
    throw std::logic_error("not param");
  }
  comand += " ";
  comand += param;
  return comand;
}
