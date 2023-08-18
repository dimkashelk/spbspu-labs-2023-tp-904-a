#include <iostream>
#include <iterator>
#include "Polygon.h"

int main()
{
  std::vector< skalisusov::Polygon> polygon;
  while(!std::cin.eof())
  {
    std::copy(std::istream_iterator< skalisusov::Polygon>(std::cin),
      std::istream_iterator<skalisusov::Polygon>(),std::back_inserter(polygon));
    if(!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
