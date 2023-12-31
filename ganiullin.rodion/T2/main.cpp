#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "DataStruct.h"

int main()
{
  using inIter = std::istream_iterator< ganiullin::DataStruct >;
  auto outIter = std::ostream_iterator< ganiullin::DataStruct >(std::cout, "\n");
  std::vector< ganiullin::DataStruct > data;
  ganiullin::Comparator comparator;

  while (!std::cin.eof()) {
    std::copy(inIter(std::cin), inIter(), std::back_inserter(data));

    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::sort(data.begin(), data.end(), comparator);
  std::copy(std::begin(data), std::end(data), outIter);

  return 0;
}
