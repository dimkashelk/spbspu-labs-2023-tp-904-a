#include "commands.hpp"
#include "dictionary.hpp"
#include <iostream>
#include "dictionaryOfCommands.hpp"


int main()
{
  dictionaryOfNames allDicts{};
  auto dictionary = DictionaryOfCommands();
  while (!std::cin.eof())
  {
    try
    {
      auto read = readCommand(std::cin);
      doCommand(read, dictionary, allDicts, std::cin, std::cout);
    }
    catch (const std::runtime_error& e)
    {
      break;
    }
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}