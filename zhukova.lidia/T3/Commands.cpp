#include "Commands.h"
namespace zhukova
{
  void getSumAreaOdd(const std::vector< Polygon > & src, std::ostream & out)
  {
    using namespace std::placeholders;
    std::vector< double > areas;
    std::transform(
      src.begin(),
      src.end(),
      std::back_inserter(areas),
      std::bind(getAreaIf, _1, isOddVertexes));
    iofmtguard fmtguard(out);
    out << std::accumulate(areas.begin(), areas.end(), 0.0) << '\n';
  }
  void getSumAreaEven(const std::vector< Polygon > & src, std::ostream & out)
  {
    using namespace std::placeholders;
    std::vector< double > areas;
    std::transform(
      src.begin(),
      src.end(),
      std::back_inserter(areas),
      std::bind(getAreaIf, _1, isEvenVertexes));
    out << std::accumulate(areas.begin(), areas.end(), 0.0) << '\n';
  }
  void getAreaMean(const std::vector< Polygon > & src, std::ostream & out)
  {
    if (src.size() == 0)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    using namespace std::placeholders;
    std::vector< double > areas;
    std::transform(
      src.begin(),
      src.end(),
      std::back_inserter(areas),
      getArea);
    iofmtguard fmtguard(out);
    double result = std::accumulate(areas.begin(), areas.end(), 0.0);
    out << result / src.size() << '\n';
  }
  void getSumAreaVertexes(const std::vector< Polygon > & src, size_t vertexes, std::ostream & out)
  {
    if (vertexes < 3)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    std::vector< double > areas;
    using namespace std::placeholders;
    std::transform(
      src.begin(),
      src.end(),
      std::back_inserter(areas),
      std::bind(getAreaIfVertexes, _1, vertexes, isAmountOfVertexes));
    double result = std::accumulate(areas.begin(), areas.end(), 0.0);
    out << result << '\n';
  }
  void getMaxMinVertexes(const std::vector< Polygon > & src, bool isMax, std::ostream & out)
  {
    std::vector< size_t > vertexesAmounts;
    std::transform(
      src.begin(),
      src.end(),
      std::back_inserter(vertexesAmounts),
      getAmountOfVertexes);
    if (isMax)
    {
      out << *std::max_element(vertexesAmounts.begin(), vertexesAmounts.end()) << '\n';
    }
    else
    {
      out << *std::min_element(vertexesAmounts.begin(), vertexesAmounts.end()) << '\n';
    }
  }
  void getMaxVertexes(const std::vector< Polygon > & src, std::ostream & out)
  {
    if (src.size() == 0)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    getMaxMinVertexes(src, true, out);
  }
  void getMinVertexes(const std::vector< Polygon > & src, std::ostream & out)
  {
    if (src.size() == 0)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    getMaxMinVertexes(src, false, out);
  }
  void getMaxMinArea(const std::vector< Polygon > & src, bool isMax, std::ostream & out)
  {
    std::vector< double > areas;
    std::transform(
      src.begin(),
      src.end(),
      std::back_inserter(areas),
      getArea);
    out << std::fixed << std::setprecision(1);
    if (isMax)
    {
      out << *std::max_element(areas.begin(), areas.end()) << '\n';
    }
    else
    {
      out << *std::min_element(areas.begin(), areas.end()) << '\n';
    }
  }
  void getMaxArea(const std::vector< Polygon > & src, std::ostream & out)
  {
    if (src.size() == 0)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    getMaxMinArea(src, true, out);
  }
  void getMinArea(const std::vector< Polygon > & src, std::ostream & out)
  {
    if (src.size() == 0)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    getMaxMinArea(src, false, out);
  }
  void countEvenOddVertexes(const std::vector< Polygon > & src, bool isEven, std::ostream & out)
  {
    if (isEven)
    {
      out << std::count_if(src.begin(), src.end(), isEvenVertexes) << '\n';
    }
    else
    {
      out << std::count_if(src.begin(), src.end(), isOddVertexes) << '\n';
    }
  }
  void countEvenVertexes(const std::vector< Polygon > & src, std::ostream & out)
  {
    countEvenOddVertexes(src, true, out);
  }
  void countOddVertexes(const std::vector< Polygon > & src, std::ostream & out)
  {
    countEvenOddVertexes(src, false, out);
  }
  void countExactVertexes(const std::vector< Polygon > & src, size_t amount, std::ostream & out)
  {
    if (amount < 3)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    using namespace std::placeholders;
    out << std::count_if(src.begin(), src.end(), std::bind(isAmountOfVertexes, _1, amount)) << '\n';
  }
  void getAmountWithLessArea(std::vector< Polygon > & src, const Polygon & border, std::ostream & out)
  {
    double borderArea = getArea(border);
    std::vector< size_t > lessAreas;
    using namespace std::placeholders;
    out << std::count_if(src.begin(), src.end(), std::bind(isLessArea, _1, borderArea)) << '\n';
  }
  void echo(std::vector< Polygon > & src, const Polygon & pol, std::ostream & out)
  {
    using namespace std::placeholders;
    std::list< Polygon > copySrc(src.begin(), src.end());
    auto comparator = std::bind(PolygonComparator(), _1, pol);
    auto samePol = std::find_if(copySrc.begin(),
                                copySrc.end(),
                                comparator);
    size_t count = 0;
    while (samePol != copySrc.end())
    {
      count++;
      copySrc.insert(samePol, pol);
      samePol = std::find_if((++samePol), copySrc.end(), comparator);;
    }
    src.assign(copySrc.begin(), copySrc.end());
    out << count << "\n";
  }
}
