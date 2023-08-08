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
  void deleteDict(dicts_list_t & list, const std::string & dict_name, std::ostream & out);
  void insertWordTranslation(dicts_list_t & list, const std::string & dict_name, const std::string & word,
                             const std::string & trans, std::ostream & out);
  void removeWordFromDict(dicts_list_t & list, const std::string & dict_name, const std::string & word,
                          std::ostream & out);
  void editWordTranslation(dicts_list_t & list, const std::string & dict_name, const std::string & word,
                           size_t num_of_translation, const std::string & new_translation, std::ostream & out);
  void addWordTranslation(dicts_list_t & list, const std::string & dict_name, const std::string & word,
                          const std::string & new_translation, std::ostream & out);
  void eraseWordTranslation(dicts_list_t & list, const std::string & dict_name, const std::string & word,
                            size_t num_of_translation, std::ostream & out);
  void printDict(dicts_list_t & list, const std::string & dict_name, std::ostream & out);
  void printDictByLetter(dicts_list_t & list, const std::string & dict_name, char letter, std::ostream & out);
  void searchWord(dicts_list_t & list, const std::string & word, std::ostream & out);
  void unionDictionaries(dicts_list_t & list, const std::string & dict1, const std::string & dict2,
                             const std::string & dict3, std::ostream & out);
  void intersectDictionaries(dicts_list_t & list, const std::string & dict1, const std::string & dict2,
                                 const std::string & dict3, std::ostream & out);
}
#endifmdcmc
