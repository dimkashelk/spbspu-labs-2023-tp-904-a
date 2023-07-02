#include <iostream>
#include "commandcontainer.h"
std::ostream &outInvalidCommand(std::ostream &out)
{
  return out << "<INVALID COMMAND>";
}
int main()
{
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

    }
  }
  return 0;
}
