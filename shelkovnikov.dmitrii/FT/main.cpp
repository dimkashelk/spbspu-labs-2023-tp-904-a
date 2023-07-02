#include <iostream>
#include <limits>
#include "commandcontainer.h"
std::ostream &outInvalidCommand(std::ostream &out)
{
  return out << "<INVALID COMMAND>";
}
int main()
{
  constexpr auto max_size = std::numeric_limits< std::streamsize >::max();
  dimkashelk::CommandContainer commandContainer(std::cin, std::cout);
  while (std::cin)
  {
    std::string command;
    std::cin >> command;
    try
    {
      commandContainer.doCommand(command);
    }
    catch (const std::logic_error &e)
    {
      outInvalidCommand(std::cout) << "\n";
      std::cin.clear();
      std::cin.ignore(max_size, '\n');
    }
  }
  return 0;
}
