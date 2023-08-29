#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>
#include "Polygon.h"
#include "Command.h"
int main(int argc, char ** argv)
{
  using namespace skalisusov;
  if(argc != 2)
  {
    std::cerr << "Not enough CL parameters\n";
    return 1;
  }
  std::ifstream input(argv[1]);
   if(!input)
   {
   std::cerr << "Not open file\n";
   return 1;
   }
   auto max = std::numeric_limits< std::streamsize>::max();
  std::vector< Polygon > polygon;
  while(!input.eof())
  {
    std::copy(std::istream_iterator< Polygon >(input),
      std::istream_iterator< Polygon >(),std::back_inserter(polygon));
    if(input.fail())
    {
      input.clear();
      input.ignore(max,'\n');
    }
  }
  input.close();
  auto mapCommand = command();
   while(!std::cin.eof())
   {
     try
     {
       std::string com = listenCommand(std::cin);
       realizationCommandPolygon(std::cin,std::cout,polygon,mapCommand,com);
     }
     catch(std::logic_error &e)
     {
       skalisusov::errorMessage(std::cout);
       std::cin.ignore(max, '\n');
     }
   }
  return 0;
}
