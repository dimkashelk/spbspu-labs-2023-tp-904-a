#include "commands.hpp"

#include <algorithm>
#include <numeric>
#include <functional>
#include <ostream>
#include <cmath>
#include <FormatGuardIO.hpp>

bool isEven(const kabanov::Polygon& pol)
{
  return pol.points.size() % 2 == 0;
}

bool isOdd(const kabanov::Polygon& pol)
{
  return !isEven(pol);
}

bool isEqualNum(const kabanov::Polygon& pol, size_t num)
{
  return pol.points.size() == num;
}

bool isEqualPoint(const kabanov::Point& p1, const kabanov::Point& p2)
{
  return p1.x == p2.x && p1.y == p2.y;
}

bool isLessVertex(const kabanov::Polygon& lnr, const kabanov::Polygon& rnl)
{
  return lnr.points.size() < rnl.points.size();
}

bool isRightAngle(
  const kabanov::Point& a,
  const kabanov::Point& b,
  const kabanov::Point& c)
{
  return (b.x - a.x) * (c.x - b.x) + (b.y - a.y) * (c.y - b.y) == 0;
}

bool hasRightAngles(std::vector< kabanov::Point > points, size_t idx)
{
  size_t n = points.size();
  const kabanov::Point& a = points[idx];
  const kabanov::Point& b = points[(idx + 1) % n];
  const kabanov::Point& c = points[(idx + 2) % n];
  return isRightAngle(a, b, c);
}

bool checkRightAngles(const kabanov::Polygon& pol)
{
  for (std::size_t i = 0; i < pol.points.size(); ++i)
  {
    if (hasRightAngles(pol.points, i))
    {
      return true;
    }
  }
  return false;
}

size_t countRightShapes(const kabanov::polygons& data)
{
  return std::count_if(data.begin(), data.end(), checkRightAngles);
}

double getTriangleArea(
  const kabanov::Point& a,
  const kabanov::Point& b,
  const kabanov::Point& c)
{
  double ab = std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
  double bc = std::sqrt(std::pow(b.x - c.x, 2) + std::pow(b.y - c.y, 2));
  double ac = std::sqrt(std::pow(c.x - a.x, 2) + std::pow(c.y - a.y, 2));
  double p = (ab + bc + ac) / 2;

  return std::sqrt(p * (p - ab) * (p - bc) * (p - ac));
}

double getArea(const kabanov::Polygon& pol)
{
  const std::vector< kabanov::Point >& points = pol.points;
  const size_t& n = points.size();

  if (n < 3)
  {
    return 0.0;
  }

  double area = 0.0;

  kabanov::Polygon temp;
  for (size_t i = 0; i < n - 2; i += 2)
  {
    area += getTriangleArea(points[i], points[i + 1], points[i + 2]);
    temp.points.push_back(points[i]);
  }

  if (isEven(pol))
  {
    area += getTriangleArea(points[n - 2], points[n - 1], points[0]);
    temp.points.push_back(points[n - 2]);
  }
  else
  {
    temp.points.push_back(points[n - 1]);
  }

  area += getArea(temp);

  return area;
}

bool compareAreas(const kabanov::Polygon& lnr, const kabanov::Polygon& rnl)
{
  return (std::fabs(getArea(lnr) - getArea(rnl)) >= std::numeric_limits< double >::epsilon())
    && (getArea(lnr) < getArea(rnl));
}

void printArea(const kabanov::polygons& pol, std::ostream& out)
{
  std::vector< double > filtered_area(pol.size());
  std::transform(pol.begin(), pol.end(), std::back_inserter(filtered_area), getArea);
  kabanov::FormatGuardIO iofmtguard(out);
  out << std::fixed << std::setprecision(1) << std::accumulate(filtered_area.begin(), filtered_area.end(), 0.0);
}

void kabanov::printAreaEven(const polygons& pol, std::ostream& out)
{
  std::vector< kabanov::Polygon > filtered;
  std::copy_if(pol.begin(), pol.end(), std::back_inserter(filtered), isEven);
  printArea(filtered, out);
}

void kabanov::printAreaOdd(const polygons& pol, std::ostream& out)
{
  std::vector< kabanov::Polygon > filtered;
  std::copy_if(pol.begin(), pol.end(), std::back_inserter(filtered), isOdd);
  printArea(filtered, out);
}

void kabanov::printAreaMean(const polygons& pol, std::ostream& out)
{
  if (pol.empty())
  {
    throw std::logic_error("No polygons");
  }
  std::vector< double > areas(pol.size());
  std::transform(pol.begin(), pol.end(), std::back_inserter(areas), getArea);
  double sum_area = std::accumulate(areas.begin(), areas.end(), 0.0);
  kabanov::FormatGuardIO iofmtguard(out);
  out << std::fixed << std::setprecision(1) << (sum_area / pol.size());
}

void kabanov::printAreaNumOfVertex(const polygons& pol, std::ostream& out, size_t num)
{
  if (num < 3)
  {
    throw std::logic_error("Not a polygon");
  }
  auto equalVertexes = std::bind(isEqualNum, std::placeholders::_1, num);
  std::vector< kabanov::Polygon > filtered;
  std::copy_if(pol.begin(), pol.end(), std::back_inserter(filtered), equalVertexes);
  printArea(filtered, out);
}

void kabanov::printMaxArea(const polygons& pol, std::ostream& out)
{
  if (pol.empty())
  {
    throw std::logic_error("No polygons");
  }
  auto res = *std::max_element(pol.begin(), pol.end(), compareAreas);
  kabanov::FormatGuardIO iofmtguard(out);
  out << std::fixed << std::setprecision(1) << getArea(res);
}

void kabanov::printMinArea(const polygons& pol, std::ostream& out)
{
  if (pol.empty())
  {
    throw std::logic_error("No polygons");
  }
  auto res = *std::min_element(pol.begin(), pol.end(), compareAreas);
  kabanov::FormatGuardIO iofmtguard(out);
  out << std::fixed << std::setprecision(1) << getArea(res);
}

void kabanov::printCountEven(const polygons& pol, std::ostream& out)
{
  auto res = std::count_if(pol.begin(), pol.end(), isEven);
  kabanov::FormatGuardIO iofmtguard(out);
  out << res;
}

void kabanov::printCountOdd(const polygons& pol, std::ostream& out)
{
  auto res = std::count_if(pol.begin(), pol.end(), isOdd);
  kabanov::FormatGuardIO iofmtguard(out);
  out << res;
}

void kabanov::printCountNumOfVertex(const polygons& pol, std::ostream& out, size_t num)
{
  if (num < 3)
  {
    throw std::logic_error("No polygons");
  }
  auto func = std::bind(isEqualNum, std::placeholders::_1, num);
  out << std::count_if(pol.begin(), pol.end(), func);
}

void kabanov::printMaxVertex(const polygons& pol, std::ostream& out)
{
  if (pol.empty())
  {
    throw std::logic_error("No polygons");
  }
  auto res = *std::max_element(pol.begin(), pol.end(), isLessVertex);
  kabanov::FormatGuardIO iofmtguard(out);
  out << res.points.size();
}

void kabanov::printMinVertex(const polygons& pol, std::ostream& out)
{
  if (pol.empty())
  {
    throw std::logic_error("No polygons");
  }
  auto res = *std::max_element(pol.begin(), pol.end(), isLessVertex);
  kabanov::FormatGuardIO iofmtguard(out);
  out << res.points.size();
}

void kabanov::printLessArea(const polygons& pol, std::ostream& out, std::istream& in)
{
  Polygon temp;
  in >> temp;
  if (!in)
  {
    throw std::logic_error("Form error");
  }
  auto count = std::count_if(pol.begin(), pol.end(), std::bind(compareAreas, std::placeholders::_1, temp));
  kabanov::FormatGuardIO iofmtguard(out);
  out << count;
}

void kabanov::printRightShapes(const polygons& pol, std::ostream& out)
{
  out << countRightShapes(pol);
}

std::ostream& kabanov::outInvalidCommandMessage(std::ostream& out)
{
  out << "<INVALID COMMAND>";
  return out;
}
