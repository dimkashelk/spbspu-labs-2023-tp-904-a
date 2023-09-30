#include "commands.hpp"
#include <algorithm>
#include <functional>
#include <numeric>
#include <stdexcept>
#include <iofmtguard.hpp>
#include "geomfigures.hpp"

namespace kotova
{
  void outFalse(std::ostream& out)
  {
    out << "<FALSE>\n";
  }
  void outTrue(std::ostream& out)
  {
    out << "<TRUE>\n";
  }

  bool isEven(const Polygon &polygon)
  {
    return polygon.points.size() % 2 ==0;
  }

  bool isOdd(const Polygon &polygon)
  {
    return !isEven(polygon);
  }

  bool calcNumVert(const Polygon &polygon, size_t cnt)
  {
    return polygon.points.size() == cnt;
  }

  size_t isCntNumVert(const Polygon &pol)
  {
    return pol.points.size();
  }

  bool compPointX(const Point &lhs, const Point &rhs)
  {
    return rhs.x > lhs.x;
  }

  bool compPointY(const Point &lhs, const Point &rhs)
  {
    return rhs.y > lhs.y;
  }

  bool compArea(const Polygon &lhs, const Polygon &rhs)
  {
    return getArea(lhs) < getArea(rhs);
  }

  bool cmpArea(const Polygon &lhs, const Polygon &rhs)
  {
    return (!compArea(lhs, rhs));
  }

  bool compVer(const Polygon &lhs, const Polygon &rhs)
  {
    return lhs.points.size() < rhs.points.size();
  }

  bool cmpVer(const Polygon &lhs, const Polygon &rhs)
  {
    return (!compVer(lhs, rhs));
  }

  bool equalPoints(const Point &lhs, const Point &rhs)
  {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }

  Point movePoint(const Point &p1, const Point &p2)
  {
    return {p1.x - p2.x, p1.y - p2.y};
  }

  double getSumArea(double area, const Polygon &pol)
  {
    return area + getArea(pol);
  }

  double getAreaEven(const std::vector<Polygon> &dest)
  {
    using namespace std::placeholders;
    std::vector< Polygon > tmp;
    std::copy_if(dest.cbegin(), dest.cend(), std::back_inserter(tmp), std::bind(isEven, _1));
    double area = std::accumulate(tmp.cbegin(), tmp.cend(), 0, getSumArea);
    return area;
  }

  double getAreaOdd(const std::vector<Polygon> &dest)
  {
    using namespace std::placeholders;
    std::vector< Polygon > tmp;
    std::copy_if(dest.cbegin(), dest.cend(), std::back_inserter(tmp), std::bind(isOdd, _1));
    double area = std::accumulate(tmp.cbegin(), tmp.cend(), 0, getSumArea);
    return area;
  }

  template< typename P >
  double getMaxOrMinArea(const std::vector< Polygon > &pol, P p)
  {
    std::vector< Polygon >::const_iterator tmp = std::max_element(pol.cbegin(), pol.cend(), p);
    return getArea(*tmp);
  }

  template< typename P >
  size_t getMaxOrMinVer(const std::vector< Polygon > & pol, P p)
  {
    std::vector< Polygon >::const_iterator tmp = std::max_element(pol.cbegin(), pol.cend(), p);
    return isCntNumVert(*tmp);
  }

  auto findPoints(const Polygon &dest)
  {
    auto minX = std::min_element(dest.points.begin(), dest.points.end(), compPointX)->x;
    auto minY = std::min_element(dest.points.begin(), dest.points.end(), compPointY)->y;
    auto maxX = std::max_element(dest.points.begin(), dest.points.end(), compPointX)->x;
    auto maxY = std::max_element(dest.points.begin(), dest.points.end(), compPointY)->y;
    Point lowerPoint{minX, minY};
    Point higherPoint{maxX, maxY};
    return std::make_pair(lowerPoint, higherPoint);
  }

  bool isSamePolygon(const Polygon &lhs, const Polygon &rhs)
  {
    if ((rhs.points.size() != lhs.points.size() || getArea(rhs) != getArea(lhs)))
    {
      return false;
    }
    auto rhsPoints = findPoints(rhs);
    auto lhsPoints = findPoints(lhs);
    Point lowerRhs{rhsPoints.first.x, rhsPoints.first.y};
    Point lowerLhs{lhsPoints.first.x, lhsPoints.first.y};
    Point higherRhs{rhsPoints.second.x, rhsPoints.second.y};
    Point higherlhs{lhsPoints.second.x, lhsPoints.second.y};
    auto diffHigher = movePoint(higherRhs, lowerRhs);
    auto diffLower = movePoint(higherlhs, lowerLhs);
    return equalPoints(diffHigher, diffLower);
  }

  void areaEven(const std::vector< Polygon > &dest, std::ostream &out)
  {
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << getAreaEven(dest) << '\n';
  }

  void areaOdd(const std::vector< Polygon > &dest, std::ostream &out)
  {
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << getAreaOdd(dest) << '\n';
  }

  void areaMean(const std::vector< Polygon > &dest, std::ostream &out)
  {
    if (dest.empty())
    {
      std::logic_error("error, there is no polygon");
    }
    std::vector< double > tmp(dest.size());
    std::transform(dest.begin(), dest.end(), tmp.begin(), getArea);
    double finAreas = std::accumulate(tmp.begin(), tmp.end(), 0.0) / dest.size();
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << finAreas << '\n';
  }

  void areaNumVertexes(size_t n, const std::vector< Polygon > &dest, std::ostream &out)
  {
    if (n < 3)
    {
      throw std::logic_error("error");
    }
    using namespace std::placeholders;
    std::vector< Polygon > tmp(dest.size());
    std::copy_if(dest.begin(), dest.end(), tmp.begin(), std::bind(calcNumVert, _1, n));
    size_t cnt = std::count_if(dest.begin(), dest.end(), std::bind(calcNumVert, _1, n));
    std::vector< double > tmp_cnt(cnt);
    auto fin_num = tmp.begin() + cnt;
    std::transform(tmp.begin(), fin_num, tmp_cnt.begin(), getArea);
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << std::accumulate(tmp_cnt.begin(), tmp_cnt.end(), 0.0) << '\n';
  }

  void maxArea(const std::vector< Polygon > &dest, std::ostream &out)
  {
    if (dest.empty())
    {
      std::logic_error("error, there is no polygon");
    }
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << getMaxOrMinArea(dest, compArea) << '\n';
  }

  void maxVertexes(const std::vector< Polygon > &dest, std::ostream &out)
  {
    if (dest.empty())
    {
      std::logic_error("error, there is no polygon");
    }
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << getMaxOrMinVer(dest, compVer) << '\n';
  }

  void minArea(const std::vector< Polygon > &dest, std::ostream &out)
  {
    if (dest.empty())
    {
      std::logic_error("error, there is no polygon");
    }
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << getMaxOrMinArea(dest, cmpArea) << '\n';
  }

  void minVertexes(const std::vector< Polygon > &dest, std::ostream &out)
  {
    if (dest.empty())
    {
      std::logic_error("error, there is no polygon");
    }
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << getMaxOrMinVer(dest, cmpVer) << '\n';
  }

  void countEven(const std::vector< Polygon > &dest, std::ostream &out)
  {
    auto cnt = std::count_if(dest.begin(), dest.end(), isEven);
    iofmtguard iofmtguard(out);
    out << cnt << "\n";
  }

  void countOdd(const std::vector< Polygon > &dest, std::ostream &out)
  {
    auto cnt = std::count_if(dest.begin(), dest.end(), isOdd);
    iofmtguard iofmtguard(out);
    out << cnt << "\n";
  }

  void countNumVertexes(size_t n, const std::vector< Polygon > &dest, std::ostream &out)
  {
    if (n < 3)
    {
      throw std::logic_error("error");
    }
    using namespace std::placeholders;
    iofmtguard iofmtguard(out);
    out << std::count_if(dest.begin(), dest.end(), std::bind(calcNumVert, _1, n)) << "\n";
  }

  void inFrame(const std::vector< Polygon > &dest, std::istream &in, std::ostream &out)
  {
    Polygon polygon;
    in >> polygon;
    if (!in)
    {
      throw std::logic_error("error");
    }
    Point lowerLhs{(*(*dest.cbegin()).points.begin()).x, (*(*dest.cbegin()).points.begin()).y};
    Point higherRhs{(*(*dest.cbegin()).points.begin()).x, (*(*dest.cbegin()).points.begin()).y};
    for (auto&& i: dest)
    {
      auto point = findPoints(i);
      lowerLhs.x = std::min(lowerLhs.x, point.first.x);
      lowerLhs.y = std::min(lowerLhs.y, point.first.y);
      higherRhs.x = std::max(higherRhs.x, point.second.x);
      higherRhs.y = std::max(higherRhs.y, point.second.y);
    }
    auto pol = findPoints(polygon);
    int polMinX = pol.first.x;
    int polMinY = pol.first.y;
    int polMaxX = pol.second.x;
    int polMaxY = pol.second.y;
    if (lowerLhs.x <= polMinX && lowerLhs.y <= polMinY && higherRhs.x >= polMaxX && higherRhs.y >= polMaxY)
    {
      outTrue(out);
    }
    else
    {
      outFalse(out);
    }
  }

  void isSame(const std::vector< Polygon > &dest, std::istream &in, std::ostream &out)
  {
    Polygon polygon;
    in >> polygon;
    if (!in)
    {
      throw std::logic_error("error");
    }
    using namespace std::placeholders;
    iofmtguard iofmtguard(out);
    out << std::count_if(dest.begin(), dest.end(), std::bind(isSamePolygon, _1, polygon)) << '\n';
  }
}
