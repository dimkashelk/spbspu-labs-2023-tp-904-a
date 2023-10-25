#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include "commands.h"
#include "commandsImpl.h"

int main()
{
  aksenov::dictOfDicts dict;
  aksenov::Commands commands;
  while (!std::cin.eof())
  {
    try
    {
      std::string command = aksenov::insertCommand(std::cin);
      aksenov::executeCommand(std::cout, std::cin, commands, dict, command);
    }
    catch (...)
    {
      return 1;
    }
  }
}
