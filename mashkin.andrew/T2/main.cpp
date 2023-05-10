#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
#include "dataStruct.h"

int main()
{
  std::vector< mashkin::DataStruct > res;
  mashkin::Comparator comp;
  while (!std::cin.eof())
  {
    /*std::copy(std::istream_iterator< mashkin::DataStruct >(std::cin), std::istream_iterator< mashkin::DataStruct >(),
        std::back_inserter(res));*/
    mashkin::DataStruct data;
    std::cin >> data;
    if (data.key3 == "error")
    {
      break;
    }
    if (std::cin.fail())
    {
      std::string line;
      std::cin.clear();
      std::getline(std::cin, line);
    }
    res.push_back(data);
  }
  std::sort(std::begin(res), std::end(res), comp);
  //::copy(std::begin(res), std::end(res), std::ostream_iterator< mashkin::DataStruct >(std::cout, "\n"));
  // std::cout << data;
  for (auto iter = res.begin(); iter < res.end(); iter++)
  {
    std::cout << *iter << "\n";
  }
  return 0;
}
