#include <vector>
#include <iterator>
#include <algorithm>
#include "datastruct.h"

int main()
{
  using vagina::DataStruct;
  std::vector< DataStruct > data;
  while (!std::cin.eof())
  {
    std::cin.clear();
    std::copy(std::istream_iterator< DataStruct >(std::cin),
      std::istream_iterator< DataStruct >(),
      std::back_inserter(data));
  }
  std::sort(data.begin(), data.end(), vagina::comp);
  std::copy(std::begin(data), std::end(data),
    std::ostream_iterator< DataStruct >(std::cout, "\n"));
  return 0;
}
