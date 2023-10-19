#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <limits>
#include <io.h>
#include <data_struct.h>
int main()
{
  using data_struct = dimkashelk::DataStruct;
  using iter_input = std::istream_iterator< data_struct >;
  auto iter_end = iter_input();
  auto out_begin = std::ostream_iterator< data_struct >(std::cout, "\n");
  dimkashelk::Comparator comparator;
  std::vector< data_struct > data;
  while (!std::cin.eof())
  {
    std::copy(iter_input(std::cin), iter_end, std::back_inserter(data));
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(data.begin(), data.end(), comparator);
  std::copy(data.begin(), data.end(), out_begin);
  return 0;
}
