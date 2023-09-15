#include "commands.h"
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <stdexcept>
#include <vector>
#include "polygon.h"
#include "solvingCommands.h"

namespace mashkin
{
  using namespace std::placeholders;

  constexpr auto maxSize = std::numeric_limits< std::streamsize >::max();

  template< class P >
  std::ostream& runEvenOrOdd(const std::deque< Polygon > res, std::ostream& out, P p)
  {
    std::deque< Polygon > data = res;
    std::deque< Polygon >::iterator it = std::partition(data.begin(), data.end(), p);
    std::vector< FullArea > areas = getFullArea(data.begin(), it);
    out << std::accumulate(areas.begin(), areas.end(), FullArea());
    return out;
  }

  std::ostream& runEven(const std::deque< Polygon >& res, std::ostream& out)
  {
    runEvenOrOdd(res, out, isEven);
    return out;
  }

  std::ostream& runOdd(const std::deque< Polygon >& res, std::ostream& out)
  {
    runEvenOrOdd(res, out, isOdd);
    return out;
  }

  void runMean(const std::deque< Polygon >& res, std::ostream& out)
  {
    std::deque< Polygon > data = res;
    size_t quantity = res.size();
    std::vector< FullArea > areas = getFullArea(data.begin(), data.end());
    std::vector< FullArea > sumArea;
    sumArea.push_back(std::accumulate(areas.begin(), areas.end(), FullArea()));
    sumArea.begin()->res /= quantity;
    std::copy(sumArea.begin(), sumArea.end(), std::ostream_iterator< FullArea >(out, "\n"));
  }

  void runAreaNumOfVertexes(const std::deque< Polygon >& res, std::ostream& out, const std::string& num)
  {
    std::deque< Polygon > data = res;
    size_t count = std::stoull(num);
    std::deque< Polygon >::iterator it = std::partition(data.begin(), data.end(), std::bind(isEqual, _1, count));
    std::vector< FullArea > areas = getFullArea(data.begin(), it);
    std::vector< FullArea > sumArea;
    sumArea.push_back(std::accumulate(areas.begin(), areas.end(), FullArea()));
    std::copy(sumArea.begin(), sumArea.end(), std::ostream_iterator< FullArea >(out, "\n"));
  }

  void runArea(std::istream& inp, std::ostream& out, const std::deque< Polygon >& res)
  {
    std::string command;
    inp >> command;
    if (command == "EVEN")
    {
      runEven(res, out) << "\n";
    }
    else if (command == "ODD")
    {
      runOdd(res, out) << "\n";
    }
    else if (command == "MEAN")
    {
      if (res.empty())
      {
        throw std::logic_error("Logic error");
      }
      else
      {
        runMean(res, out);
      }
    }
    else if (command.find_first_not_of("0123456789") == std::string::npos)
    {
      if (command == "0" || command == "1" || command == "2")
      {
        throw std::logic_error("Logic error");
      }
      else
      {
        runAreaNumOfVertexes(res, out, command);
      }
    }
    else
    {
      throw std::logic_error("Logic error");
    }
  }

  void runMaxArea(const std::deque< Polygon >& res, std::ostream& out)
  {
    std::deque< Polygon > data = res;
    std::vector< FullArea > areas = getFullArea(data.begin(), data.end());
    std::sort(areas.begin(), areas.end());
    std::copy(--areas.end(), areas.end(), std::ostream_iterator< FullArea >(out, "\n"));
  }

  std::ostream& runMaxVertexes(const std::deque< Polygon >& res, std::ostream& out)
  {
    std::deque< Polygon > data = res;
    std::sort(data.begin(), data.end());
    std::deque< Polygon >::iterator it = --data.end();
    out << it->points.size();
    return out;
  }

  void runMax(std::istream& inp, std::ostream& out, const std::deque< Polygon >& data)
  {
    std::string command;
    inp >> command;
    if (data.empty())
    {
      throw std::logic_error("Logic error");
    }
    else if (command == "AREA")
    {
      runMaxArea(data, out);
    }
    else if (command == "VERTEXES")
    {
      runMaxVertexes(data, out) << "\n";
    }
    else
    {
      throw std::logic_error("Logic error");
    }
  }

  void runMinArea(const std::deque< Polygon >& res, std::ostream& out)
  {
    std::deque< Polygon > data = res;
    std::vector< FullArea > areas = getFullArea(data.begin(), data.end());
    std::sort(areas.begin(), areas.end());
    std::copy(areas.begin(), ++areas.begin(), std::ostream_iterator< FullArea >(out, "\n"));
  }

  std::ostream& runMinVertexes(const std::deque< Polygon >& res, std::ostream& out)
  {
    std::deque< Polygon > data = res;
    std::sort(data.begin(), data.end());
    std::deque< Polygon >::iterator it = data.begin();
    out << it->points.size();
    return out;
  }

  void runMin(std::istream& inp, std::ostream& out, const std::deque< Polygon >& res)
  {
    std::string command;
    inp >> command;
    if (res.empty())
    {
      throw std::logic_error("Logic error");
    }
    else if (command == "AREA")
    {
      runMinArea(res, out);
    }
    else if (command == "VERTEXES")
    {
      runMinVertexes(res, out) << "\n";
    }
    else
    {
      throw std::logic_error("Logic error");
    }
  }

  std::ostream& runCountEven(const std::deque< Polygon >& res, std::ostream& out)
  {
    std::deque< Polygon > data = res;
    size_t quantity = std::count_if(data.begin(), data.end(), isEven);
    out << quantity;
    return out;
  }

  std::ostream& runCountOdd(const std::deque< Polygon >& res, std::ostream& out)
  {
    std::deque< Polygon > data = res;
    size_t quantity = std::count_if(data.begin(), data.end(), isOdd);
    out << quantity;
    return out;
  }

  std::ostream& runCountNumOfVertexes(const std::deque< Polygon >& res, std::ostream& out, const std::string& command)
  {
    std::deque< Polygon > data = res;
    size_t count = std::stoull(command);
    size_t quantity = std::count_if(data.begin(), data.end(), std::bind(isEqual, _1, count));
    std::cout << quantity;
    return out;
  }

  void runCount(std::istream& inp, std::ostream& out, const std::deque< Polygon >& res)
  {
    std::string command;
    inp >> command;
    if (command == "EVEN")
    {
      if (res.empty())
      {
        out << 0 << "\n";
      }
      else
      {
        runCountEven(res, out) << "\n";
      }
    }
    else if (command == "ODD")
    {
      if (res.empty())
      {
        out << 0 << "\n";
      }
      else
      {
        runCountOdd(res, out) << "\n";
      }
    }
    else if (command.find_first_not_of("0123456789") == std::string::npos)
    {
      if (command == "0" || command == "1" || command == "2")
      {
        throw std::logic_error("Logic error");
      }
      else
      {
        runCountNumOfVertexes(res, out, command) << "\n";
      }
    }
    else
    {
      throw std::logic_error("Logic error");
    }
  }

  void runPerms(std::istream& inp, std::ostream& out, const std::deque< Polygon >& res)
  {
    std::deque< Polygon > data = res;
    Polygon comp;
    inp >> comp;
    if (inp.fail())
    {
      throw std::logic_error("Logic error");
    }
    std::sort(comp.points.begin(), comp.points.end());
    size_t quantity = 0;
    quantity = std::count_if(data.begin(), data.end(), std::bind(isEqualPoints, _1, comp));
    out << quantity << "\n";
  }

  void runRightshapes(std::istream&, std::ostream& out, const std::deque< Polygon >& res)
  {
    size_t quantity = std::count_if(res.begin(), res.end(), isRightShapes);
    out << quantity << "\n";
  }
}
