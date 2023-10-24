#include <algorithm>
#include <cctype>
#include <sstream>

#include "commands.h"
int main()
{
  using namespace aristarkhov;
  dictionaryOfNames dictionaries;

  while (!std::cin.eof())
  {
    try
    {
      std::string cmd = "";
      std::cin >> cmd;
      processCommand(dictionaries, cmd, std::cin, std::cout);
    }
    catch (const std::logic_error& e)
    {
      std::cout << "Error: " << e.what() << '\n';
      skipUntilNewLine(std::cin);
    }
    catch (const std::runtime_error& e)
    {
      std::cout << "Error: " << e.what() << '\n';
      skipUntilNewLine(std::cin);
    }
  }
  return 0;
}
