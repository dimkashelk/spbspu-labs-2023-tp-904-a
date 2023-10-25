#include <iostream>
#include <limits>
#include "Coding.h"
#include "Encoding.h"
#include "Commands.h"
#include "CommandSystem.h"
int main()
{
  setlocale(LC_ALL, "Russian");
  zhukova::TextDict texts;
  zhukova::EncodingDict encodings;

  zhukova::CommandSystem commands = zhukova::makeCommandSystem();
  while (!std::cin.eof())
  {
    try
    {
      std::string comm = zhukova::inputCommand(std::cin);
      zhukova::doCommand(texts, encodings, commands, comm, std::cin,std::cout);
    }
    catch (const std::runtime_error & e)
    {
      break;
    }
    catch (const std::invalid_argument & e)
    {
      std::cout << e.what() << "\n";
    }
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
