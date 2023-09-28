#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include <limits>
#include "Geometry.h"
#include "CommandSystem.h"
#include "DataIO.h"
std::ostream &outInvalidCommand(std::ostream &out)
{
  return out << "<INVALID COMMAND>\n";
}
int main(int argc, char * argv[])
{
  if (argc < 2) {
    return 1;
  }
  std::ifstream inFile(argv[1]);
  if (!inFile.is_open())
  {
    std::cerr << "file was not opened\n";
    return 1;
  }
  std::vector< zhukova::Polygon > dataVector;
  using in_iter = std::istream_iterator< zhukova::Polygon >;
  while (!inFile.eof())
  {
    std::copy(in_iter(inFile), in_iter(), std::back_inserter(dataVector));
    if (!inFile)
    {
      inFile.clear();
      inFile.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  inFile.close();
  std::cout << std::fixed << std::setprecision(1);
  zhukova::CommandSystem commands = zhukova::makeCommandSystem();
  while (!std::cin.eof())
  {
    try {
      std::string comm = zhukova::inputCommand(std::cin);
      zhukova::doCommand(dataVector, commands,
                         comm, std::cin, std::cout);
    }
    catch (std::runtime_error & e) {
      break;
    }
    catch (std::logic_error & e){
      outInvalidCommand(std::cout);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    if (!std::cin) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
