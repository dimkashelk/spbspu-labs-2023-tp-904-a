#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <iterator>

#include "commands_dict.hpp"
#include "commands.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Wrong amount of arguments\n";
    return 1;
  }
  std::ifstream in(argv[1]);
  if (!in)
  {
    std::cerr << "File didn't open\n";
    return 2;
  }
  using insIter = std::istream_iterator< kabanov::Polygon >;
  kabanov::polygons data;

  while (!in.eof())
  {
    std::copy(insIter(in), insIter(), std::back_inserter(data));
    if (!in)
    {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  kabanov::CommandContainer commandContainer;
  while (!std::cin.eof())
  {
    try
    {
      commandContainer.doCommand(commandContainer.inputCommand(std::cin), data, std::cout, std::cin);
      std::cout << '\n';
    }
    catch (const std::logic_error& e)
    {
      kabanov::outInvalidCommandMessage(std::cout) << '\n';
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      std::cin.clear();
    }
    catch (const std::runtime_error& e)
    {
      break;
    }
  }
  return EXIT_SUCCESS;
}
