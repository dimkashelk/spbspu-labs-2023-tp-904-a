#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#include <algorithm>
#include <iterator>
#include <cassert>
#include <vector>
#include <limits>

#include "data-struct.hpp"

int main()
{
  using turkin::DataStruct;
  using turkin::Comparator;
  using isit = std::istream_iterator< DataStruct >;
  using osit = std::ostream_iterator< DataStruct >;

  std::vector< DataStruct > data;
  Comparator cmp;
  
  while (!std::cin.eof())
  {
    std::copy(isit(std::cin), isit(), std::back_inserter(data));
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(data.begin(), data.end(), cmp);
  std::copy(data.begin(), data.end(), osit(std::cout, "\n"));

  return 0;
}
