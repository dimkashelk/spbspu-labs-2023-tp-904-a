#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cmath>
#include <vector>
#include "Command.h"
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
  out << std::setprecision(1) << areaSum << '\n';
}

void skalisusov::areaOdd(const std::vector<Polygon> &dest, std::ostream &out)
{
  std::vector< Polygon > evePoly;
  std::copy_if(dest.begin(), dest.end(),std::back_inserter(evePoly), isOdd);
  std::vector< double > areaVector(evePoly.size());
  std::transform(std::begin(evePoly),std::end(evePoly),std::begin(areaVector), getArea);
  auto areaSum = std::accumulate(std::begin(areaVector),std::end(areaVector), 0.0);
  out << std::setprecision(1) << areaSum << '\n';
}
void skalisusov::areaMean(const std::vector<Polygon> &dest, std::ostream &out)
{
  if(dest.empty())
  {
    throw std::logic_error("Polygon is empty");
  }
  size_t count = dest.size();
  std::vector< double > areaVector(dest.size());
  std::transform(std::begin(dest),std::end(dest),std::begin(areaVector), getArea);
  auto areaSum = std::accumulate(std::begin(areaVector),std::end(areaVector),0.0);
  areaSum = areaSum / count;
  out << std::setprecision(1) << areaSum << '\n';
}
void skalisusov::areaNumOfVertex(const std::vector< Polygon > &dest, size_t vertex, std::ostream &out)
{
  if( vertex < 3)
  {
    throw std::logic_error("Invalied parameter");
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
    throw std::logic_error("Polygon is empty");
  }
  std::vector< Polygon > polygon(dest.size());
  std::copy(std::begin(dest),std::end(dest),std::begin(polygon));
  std::vector< double > area(polygon.size());
  std::transform(std::begin(polygon),std::end(polygon),std::begin(area), getArea);
  auto compar = [&](double a, double b){return a < b;};
  std::sort(std::begin(area),std::end(area),compar);
  double maxArea = area[area.size() - 1];
  out << std::setprecision(1) << maxArea << '\n';
}
void skalisusov::maxVertex(const std::vector< Polygon > &dest, std::ostream &out)
{
  if(dest.empty())
  {
    throw std::logic_error("Polygon is empty");
  }
  std::vector< Polygon > polgon(dest.size());
  std::copy(std::begin(dest),std::end(dest),std::begin(polgon));
  std::sort(std::begin(polgon),std::end(polgon),skalisusov::comparator);
  auto end = polgon[polgon.size()-1];
  size_t maxVertex = end.polygon.size();
  out << maxVertex << '\n';
}
void skalisusov::minArea(const std::vector<Polygon> &dest, std::ostream &out)
{
  if(dest.empty())
  {
    throw std::logic_error("Polygon is empty");
  }
  std::vector< Polygon > polygon(dest.size());
  std::copy(std::begin(dest),std::end(dest),std::begin(polygon));
  std::vector< double > area(polygon.size());
  std::transform(std::begin(polygon),std::end(polygon),std::begin(area), getArea);
  std::sort(std::begin(area),std::end(area));
  double minArea = area[0];
  out << std::setprecision(1) << minArea << '\n';
}
void skalisusov::minVertex(const std::vector<Polygon> &dest, std::ostream &out)
{
  if(dest.empty())
  {
    throw std::logic_error("Polygon is empty");
  }
  std::vector< Polygon > polgon(dest.size());
  std::copy(std::begin(dest),std::end(dest),std::begin(polgon));
  auto compare = [&](Polygon lhs, Polygon rhs)
  {return lhs.polygon.size() < rhs.polygon.size();};
  std::sort(std::begin(polgon),std::end(polgon),compare);
  auto min = polgon[0];
  std::size_t minVertex = min.polygon.size();
  out << minVertex << '\n';
}
void skalisusov::countEven(const std::vector<Polygon> &dest, std::ostream &out)
{
  std::vector< Polygon > polygon;
  std::copy_if(std::begin(dest),std::end(dest),std::back_inserter(polygon), isEven);
  size_t count = polygon.size();
  out << count << '\n';
}
void skalisusov::countOdd(const std::vector<Polygon> &dest, std::ostream &out)
{
  std::vector< Polygon > polygon;
  std::copy_if(std::begin(dest),std::end(dest),std::back_inserter(polygon), isOdd);
  size_t count = polygon.size();
  out << count << '\n';
}
void skalisusov::countVertex(const std::vector<Polygon> &dest, size_t vertex, std::ostream &out)
{
  using namespace std::placeholders;
  auto numVertex = std::bind(isNumVertex,_1,vertex);
  std::vector< Polygon > polygon;
  std::copy_if(std::begin(dest),std::end(dest),std::back_inserter(polygon),numVertex);
  size_t shapesThisVertex = polygon.size();
  out << shapesThisVertex << '\n';
}

void skalisusov::rects(const std::vector<Polygon> &dest, std::ostream &out)
{
  std::vector< Polygon > polygon;
  std::copy_if(std::begin(dest),std::end(dest),std::back_inserter(polygon), isRects);
  std::size_t countRects = polygon.size();
  out << countRects << '\n';
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
void skalisusov::errorMessage(std::ostream &out)
{
  out << "<INVALID COMMAND>\n";
}
skalisusov::commandPolygon skalisusov::command()
{
  skalisusov::commandPolygon mapCommand{};
  mapCommand.const_area.insert({"AREA EVEN", areaEven});
  mapCommand.const_area.insert({"AREA ODD", areaOdd});
  mapCommand.const_area.insert({"AREA MEAN", areaMean});
  mapCommand.const_area.insert({"MAX AREA", maxArea});
  mapCommand.const_area.insert({"MAX VERTEXES", maxVertex});
  mapCommand.const_area.insert({"MIN AREA", minArea});
  mapCommand.const_area.insert({"MIN VERTEXES", minVertex});
  mapCommand.const_area.insert({"COUNT EVEN", countEven});
  mapCommand.const_area.insert({"COUNT ODD", countOdd});
  mapCommand.const_area.insert({"RECTS", rects});
  mapCommand.const_ver.insert({"AREA NUM", areaNumOfVertex});
  mapCommand.const_ver.insert({"COUNT NUM", countVertex});
  mapCommand.area.insert({"LESSAREA", rmecho});
  return mapCommand;
}
void skalisusov::realizationCommandPolygon(std::istream &in,std::ostream &out, std::vector< Polygon > &dest
                                           ,const skalisusov::commandPolygon &commands,std::string &command)
{
  using namespace std::placeholders;
  try
  {
    auto polygon = std::bind(commands.area.at(command), _1,std::ref(in),std::ref(out));
    polygon(dest);
    return;
  }
  catch (const std::out_of_range & e)
  {}
  try
  {
    auto polygon = std::bind(commands.const_area.at(command), _1, std::ref(out));
    polygon(dest);
    return;
  }
  catch (const std::out_of_range & e)
  {}
  std::size_t space = command.find(' ');
  std::size_t num = std::stoull(command.substr(space));
  auto vertexes = std::bind(commands.const_ver.at(command.substr(0, space) + " NUM"),
                            _1,num,std::ref(out));
  vertexes(dest);
}
std::string skalisusov::listenCommand(std::istream &in)
{
  std::string comand = "0";
  in >> comand;
  if(!in)
  {
    throw std::logic_error("not input");
  }
  if(comand == "RECTS" || comand == "LESSAREA")
  {
    return comand;
  }
  std::string param = "0";
  in >> param;
  if(!in)
  {
    throw std::logic_error("not param");
  }
  comand += " ";
  comand += param;
  return comand;
}
void skalisusov::rmecho(std::vector< Polygon > &dest, std::istream &in, std::ostream &out)
{
  Polygon shape;
  in >> shape;
  if(shape.polygon.size() < 3)
  {
    throw std::logic_error("Invalid parameters");
  }
  size_t count = 0;
  count = function_for_rmecho(dest,shape);
  out << count;
}
size_t skalisusov::function_for_rmecho(std::vector< Polygon > &poly, skalisusov::Polygon &rhs)
{
  size_t count = 0;
  std::vector< Polygon > data(poly.size());
  std::copy(std::begin(poly),std::end(poly),std::begin(data));
  auto it_1 = std::adjacent_find(data.begin(),data.end());
  while( it_1 != data.end())
  {
    auto next = std::adjacent_find(it_1++,data.end());
    if(next != data.end() && next->polygon == it_1->polygon && next->polygon == rhs.polygon)
    {
      data.erase(it_1,next+1);
      count++;
    }
    else
    {
      it_1 = next;
    }
  }
  poly = data;
  return count;
}
