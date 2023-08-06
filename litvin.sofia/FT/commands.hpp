#ifndef FT_COMMANDS_HPP
#define FT_COMMANDS_HPP
#include <map>
#include <iostream>
#include <string>
#include "dict.hpp"
namespace litvin
{
  void createNewDict(dicts_list_t & list, const std::string & dict_name, std::ostream & out);
  void deleteDict(dicts_list_t & list, const std::string & dict_name, std::ostream & out);
  void insertWordTranslation(dicts_list_t & list, const std::string & dict_name, const std::string & word,
                             const std::string & trans, std::ostream & out);
  void removeWordFromDict(dicts_list_t & list, const std::string & dict_name, const std::string & word,
                          std::ostream & out);
  bool findDict(const dicts_list_t & list, const std::string & dict_name);
  translations* findWordTranslation(dicts_list_t & list, const std::string & dict_name, const std::string & word);
}
#endif
