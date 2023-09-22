#include <iostream>
#include <fstream>
#include <iterator>
#include <functional>
#include <limits>
#include "read-and-do-command.hpp"

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cerr << "Not correct number of CML args\n";
    return 1;
  }
  std::ifstream ifstream(argv[1]);
  if (!ifstream.is_open())
  {
    std::cerr << "The file doesn't open\n";
    return 1;
  }

  std::vector< chemodurov::Polygon > data;
  constexpr auto max_size = std::numeric_limits< std::streamsize >::max();
  while (!ifstream.eof())
  {
    if (ifstream.fail())
    {
      ifstream.clear();
      ifstream.ignore(max_size, '\n');
    }
    using is_it_t = std::istream_iterator< chemodurov::Polygon >;
    std::copy(is_it_t(ifstream), is_it_t(), std::back_inserter(data));
  }
  auto commands = chemodurov::createCommandDictionary();
  auto read = std::bind(chemodurov::readCommand, std::ref(std::cin));
  auto doComm = std::bind(chemodurov::doCommand, read, commands, data, std::ref(std::cin), std::ref(std::cout));
  do
  {
    try
    {
      doComm();
    }
    catch (const std::logic_error & e)
    {
      chemodurov::outInvalidCommand(std::cout);
      std::cout << '\n';
      std::cin.ignore(max_size, '\n');
    }
    catch (const std::runtime_error & e)
    {
      break;
    }
  }
  while (!std::cin.eof());
  return 0;
}
