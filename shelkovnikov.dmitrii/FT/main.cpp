#include <iostream>
#include <limits>
#include "commandcontainer.h"
std::ostream &outInvalidCommand(std::ostream &out)
{
  return out << "<INVALID COMMAND>";
}
std::ostream &outErrorFile(std::ostream &out)
{
  return out << "Can't open file";
}
void skipCommand(std::istream &in)
{
  constexpr auto max_size = std::numeric_limits< std::streamsize >::max();
  in.clear();
  in.ignore(max_size, '\n');
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
      outInvalidCommand(std::cout) << "\n";
      skipCommand(std::cin);
    }
    catch (const std::runtime_error &e)
    {
      outErrorFile(std::cout) << "\n";
      skipCommand(std::cin);
    }
  }
  return 0;
}
