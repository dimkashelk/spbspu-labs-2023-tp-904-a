#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>
#include "Command.h"
int main(int argc, char ** argv)
{
  if (argc < 2)
  {
    std::cerr << "Not enough CL parameters\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Not open file\n";
   return 1;
  }
  auto max = std::numeric_limits< std::streamsize>::max();
  std::vector< skalisusov::Polygon > data;
  while (!input.eof())
  {
    std::copy(std::istream_iterator< skalisusov::Polygon >(input),
      std::istream_iterator< skalisusov::Polygon >(),std::back_inserter(data));
    if (input.fail())
    {
      input.clear();
      input.ignore(max,'\n');
    }
  }
  input.close();
  auto mapCommand = skalisusov::command();
  while (!std::cin.eof())
  {
    try
    {
      std::string com = mapCommand.listenCommand(std::cin);
      mapCommand.CommandPolygon(std::cin,std::cout,data,mapCommand,com);
    }
    catch (const std::runtime_error &e)
    {
      break;
    }
    catch (const std::logic_error &e)
    {
      skalisusov::errorMessage(std::cout);
      std::cin.ignore(max, '\n');
    }
  }
  return 0;
}
