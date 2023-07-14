#ifndef FT_COMMANDCONTAINER_H
#define FT_COMMANDCONTAINER_H
#include <iostream>
#include "commands.h"
#include "io.h"
using func_with_istream = void(*)(all_data &, std::istream &);
using func_with_ostream = void(*)(std::ostream &);
using func_with_iostream = void(*)(all_data &, std::istream &, std::ostream &);
namespace dimkashelk
{
  class CommandContainer
  {
  public:
    CommandContainer(std::istream &in, std::ostream &out);
    void doCommand(const std::string &command);
  private:
    std::istream &in_;
    std::ostream &out_;
    all_data data_;
    std::map< std::string, func_with_istream > dictWithIstream_;
    std::map< std::string, func_with_ostream > dictWithOstream_;
    std::map< std::string, func_with_iostream > dictWithIOstream_;
    std::map< std::string, func_with_istream > initializeIstream();
    std::map< std::string, func_with_ostream > initializeOstream();
    std::map< std::string, func_with_iostream > initializeIOstream();
    std::string inputString();
    std::pair< std::string, std::string > input2String();
    std::tuple< std::string, std::string, std::string > input3String();
    size_t inputSizeT();
  };
}
#endif
