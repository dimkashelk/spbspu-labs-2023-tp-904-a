#include <algorithm>
#include <cctype>
#include <sstream>

#include "commands.h"
#include "dictionaryCommands.h"

int main()
{
  using namespace aristarkhov;
  dictionaryOfNames dictionaries;
  CommandProcessor commandProcessor;

  try
  {
    commandProcessor.printHelp(dictionaries, std::cin, std::cout);
  }
  catch (const std::logic_error& e)
  {
    std::cout << "Error: " << e.what() << '\n';
    skipUntilNewLine(std::cin);
  }

  while (!std::cin.eof())
  {
    try
    {
      std::string cmd = "";
      std::cin >> cmd;
      commandProcessor.processCommand(dictionaries, cmd, std::cin, std::cout);
    }
    catch (const std::exception& e)
    {
      std::cout << "Error: " << e.what() << '\n';
      skipUntilNewLine(std::cin);
    }
  }
  return 0;
}
