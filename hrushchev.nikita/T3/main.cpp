#include <iostream>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <deque>
#include "polygon.hpp"
#include "command.hpp"
#include "workwithdict.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cout << "Error arg\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input.is_open())
  {
    std::cout << "Error file\n";
    return 1;
  }

  std::vector< hrushchev::Polygon > data;
  while (!input.eof())
  {
    if (!input)
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    using iter = std::istream_iterator< hrushchev::Polygon >;
    std::copy(iter(input), iter(), std::back_inserter(data));
  }

  hrushchev::Commands dict_wiht_cmd;

  while (!std::cin.eof())
  {
    try
    {
      std::string command;
      command = hrushchev::inputCommand(std::cin);
      hrushchev::doCommand(data, dict_wiht_cmd, command, std::cout, std::cin);
    }
    catch (const std::exception& e)
    {
      std::cout << "<INVALID COMMAND>" << "\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
