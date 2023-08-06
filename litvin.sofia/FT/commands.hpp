#ifndef FT_COMMANDS_HPP
#define FT_COMMANDS_HPP
#include <map>
#include <iostream>
#include <string>
#include "dict.hpp"
namespace litvin
{
  void createNewDict(list_of_dicts_t & list, const std::string & dict_name, std::ostream & out);
  void deleteDict(list_of_dicts_t & list, const std::string & dict_name, std::ostream & out);
}
#endif
