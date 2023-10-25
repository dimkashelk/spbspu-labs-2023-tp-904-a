#ifndef FT_COMMANDS_HPP
#define FT_COMMANDS_HPP
#include <map>
#include <iostream>
#include <string>
#include "dict.hpp"
namespace litvin
{
  bool findDict(const dicts_list_t & list, const std::string & dict_name);
  translations * findWordTranslation(dicts_list_t & list, const std::string & dict_name, const std::string & word);
  void createNewDict(dicts_list_t & list, const std::string & dict_name, std::ostream & out);
  void deleteDict(dicts_list_t & list, std::ostream & out, std::istream & in);
  void insertWordTranslation(dicts_list_t & list, std::ostream & out, std::istream & in);
  void removeWordFromDict(dicts_list_t & list, std::ostream & out, std::istream & in);
  void editWordTranslation(dicts_list_t & list, std::ostream & out, std::istream & in);
  void addWordTranslation(dicts_list_t & list, std::ostream & out, std::istream & in);
  void eraseWordTranslation(dicts_list_t & list, std::ostream & out, std::istream & in);
  void printDict(dicts_list_t & list, std::ostream & out, std::istream & in);
  void printDictByLetter(dicts_list_t & list, std::ostream & out, std::istream & in);
  void searchWord(dicts_list_t & list, std::ostream & out, std::istream & in);
  void unionDictionaries(dicts_list_t & list, std::ostream & out, std::istream & in);
  void intersectDictionaries(dicts_list_t & list, std::ostream & out, std::istream & in);
  void subtractDictionaries(dicts_list_t & list, std::ostream & out, std::istream & in);
}
#endif
