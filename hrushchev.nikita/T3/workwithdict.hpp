#ifndef WORKWITHDICT_HPP
#define WORKWITHDICT_HPP

#include <map>
#include "polygon.hpp"

namespace hrushchev
{
  class Commands
  {
    private:
      using com1 = void (*)(const std::vector< Polygon >& polygons, std::ostream& out);
      using com2 = void (*)(const std::vector< Polygon >& polygons, size_t count, std::ostream& out);
      using com3 = void (*)(std::vector< Polygon >& polygons, const Polygon& polygon, std::ostream& out);
      std::map< std::string, com1 > dict1_;
      std::map< std::string, com2 > dict2_;
      std::map< std::string, com3 > dict3_;
  };
}
#endif
