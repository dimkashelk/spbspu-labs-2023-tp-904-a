#include "commands.h"
#include <algorithm>
#include <numeric>

bool vagina::isEven(const Polygon & pol)
{
  return (pol.points.size() % 2 == 0);
}

bool vagina::isCountOfVertexes(const Polygon& pol, std::size_t param)
{
  return (pol.points.size() == param);
}

void vagina::areaEven(const std::vector< Polygon >& dest, std::ostream& out)
{
  std::vector< Polygon > tmp;
  std::copy_if(dest.begin(), dest.end(), tmp.begin(),
    [&](Polygon i) { return isEven(i); });
  std::vector< double > tmpS(tmp.size());
  std::transform(tmp.begin(), tmp.end(), tmpS.begin(), getArea);
  out << std::setprecision(1) << std::accumulate(tmpS.begin(), tmpS.end(), 0.0) << "\n";
}

void vagina::areaOdd(const std::vector< Polygon >& dest, std::ostream& out)
{
  std::vector< Polygon > tmp;
  std::copy_if(dest.begin(), dest.end(), tmp.begin(),
    [&](Polygon i) { return !isEven(i); });
  std::vector< double > tmpS(tmp.size());
  std::transform(tmp.begin(), tmp.end(), tmpS.begin(), getArea);
  out << std::setprecision(1) << std::accumulate(tmpS.begin(), tmpS.end(), 0.0) << "\n";
}

void vagina::areaMean(const std::vector< Polygon >& dest, std::ostream& out)
{
  if (dest.empty())
  {
    messageInvalidCommand(out);
    return;
  }
  std::vector< double > tmp(dest.size());
  std::transform(dest.begin(), dest.end(), tmp.begin(), getArea);
  out << std::setprecision(1) << std::accumulate(tmp.begin(), tmp.end(), 0.0) / dest.size() << "\n";
}

void vagina::areaVertexes(const std::vector< Polygon >& dest, std::ostream& out, std::size_t param)
{
  std::vector< Polygon > tmp(dest.size());
  std::copy_if(dest.begin(), dest.end(), tmp.begin(),
    [&](Polygon i) { return isCountOfVertexes(i, param); });
  std::vector< double > tmpS(tmp.size());
  std::transform(tmp.begin(), tmp.end(), tmpS.begin(), getArea);
  out << std::setprecision(1) << std::accumulate(tmpS.begin(), tmpS.end(), 0.0) << "\n";
}

void vagina::maxArea(const std::vector < Polygon >& dest, std::ostream& out)
{
  if (dest.empty())
  {
    messageInvalidCommand(out);
    return;
  }
  std::vector< Polygon > tmp(dest.size());
  std::copy(dest.begin(), dest.end(), tmp.begin());
  std::sort(tmp.begin(), tmp.end(), comparatorArea);
  out << std::setprecision(1) << getArea(tmp[0]) << "\n";
}

void vagina::maxVertexes(const std::vector < Polygon >& dest, std::ostream& out)
{
  if (dest.empty()) {
    messageInvalidCommand(out);
    return;
  }
  std::vector< Polygon > tmp(dest.size());
  std::copy(dest.begin(), dest.end(), tmp.begin());
  std::sort(tmp.begin(), tmp.end(), comparatorVertexes);
  out << std::setprecision(1) << tmp[0].points.size() << "\n";
}

void vagina::minArea(const std::vector < Polygon >& dest, std::ostream& out)
{
  if (dest.empty())
  {
    messageInvalidCommand(out);
    return;
  }
  std::vector< Polygon > tmp(dest.size());
  std::copy(dest.begin(), dest.end(), tmp.begin());
  std::sort(tmp.begin(), tmp.end(), comparatorArea);
  out << std::setprecision(1) << getArea(tmp[tmp.size() - 1]) << "\n";
}
void vagina::minVertexes(const std::vector < Polygon >& dest, std::ostream& out)
{
  if (dest.empty()) {
    messageInvalidCommand(out);
    return;
  }
  std::vector< Polygon > tmp(dest.size());
  std::copy(dest.begin(), dest.end(), tmp.begin());
  std::sort(tmp.begin(), tmp.end(), comparatorVertexes);
  out << std::setprecision(1) << tmp[0].points.size() << "\n";
}
void vagina::messageInvalidCommand(std::ostream& out)
{
  out << "<INVALID COMMAND>\n";
}
