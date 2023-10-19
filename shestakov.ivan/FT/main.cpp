#include <iostream>
#include "auxiliary_commands.h"
#include "read_and_do_commands.h"

int main()
{
  using namespace shestakov;
  std::map< std::string, Dictionary > dicts_;

  while(!std::cin.eof())
  {
    try
    {
      std::string cmd = "";
      std::cin >> cmd;
      doCommand(dicts_, cmd, std::cin, std::cout);
    }
    catch (const std::logic_error& e)
    {
      printError(std::cout);
      skipUntilNewLine(std::cin);
      std::cout << '\n';
    }
  }
  return 0;
}
