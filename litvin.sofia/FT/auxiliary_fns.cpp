#include "auxiliary_fns.hpp"
litvin::command_dict_t::command_dict_t()
{
  dict1.insert({"SEARCH", searchWord});
  dict1.insert({"PRINT", printDict});
  dict1.insert({"DELETE", deleteDict});
  dict1.insert({"NEW", createNewDict});
  dict2.insert({"INSERT", insertWordTranslation});
  dict2.insert({"ADD", addWordTranslation});
  dict2.insert({"INTERSECT", intersectDictionaries});
  dict2.insert({"UNION", unionDictionaries});
  dict2.insert({"DIFFERENCE", subtractDictionaries});
  dict3.insert({"REMOVE", removeWordFromDict});
  dict3.insert({"PRINTL", printDictByLetter});
  dict4.insert({"EDIT", editWordTranslation});
  dict5.insert({"ERASE", eraseWordTranslation});
  dict6.insert({"HELP", help});
  dict7.insert({"MAN", man});
}
litvin::command_descriptors litvin::createCommandDescriptorsDict()
{
  command_descriptors dict;
  dict.insert({"SEARCH", "Searches word translation in all available dictionaries"});
  dict.insert({"PRINT", "Prints all dictionary with its words and their translations"});
  dict.insert({"DELETE", "Deletes dictionary with name, equal to argument"});
  dict.insert({"NEW", "Creates new empty dictionary with name, equal to argument"});
  dict.insert({"INSERT", "Inserts the word to the dict with translation"});
  dict.insert({"ADD", "Adds new translation to the word"});
  dict.insert({"INTERSECT", "Creates a dict, which is intersection of two already existing dicts"});
  dict.insert({"UNION", "Creates a dict, which is union of two already existing dicts"});
  dict.insert({"DIFFERENCE", "Creates a dict, which is subtraction of two already existing dicts"});
  dict.insert({"REMOVE", "Removes the word from dictionary with its translation list"});
  dict.insert({"PRINTL", "Prints words and their translations from dict starting by the letter-parameter"});
  dict.insert({"EDIT", "Edits the word translation by number-parameter"});
  dict.insert({"ERASE", "Erases the word translation by number-parameter"});
  dict.insert({"MAN", "Gives info about requested command"});
  dict.insert({"HELP", "Gives info about all available commands"});
  return dict;
}
void litvin::man(const command_descriptors & cmd_desc, const std::string & command, std::ostream & out)
{
  try
  {
    out << cmd_desc.at(command);
  }
  catch (const std::out_of_range &)
  {
    out << "This command does not exists, see 'help'\n";
  }
}
void litvin::help(const command_descriptors & cmd_desc, std::ostream & out)
{
  for (const auto & desc: cmd_desc)
  {
    out << desc.first << " " << desc.second << '\n';
  }
}
void litvin::command_dict_t::executeCommand(const std::string & command, dicts_list_t & list, const std::string & str,
                                            std::ostream & out)
{
  signature_type_1 function = dict1.at(command);
  function(list, str, out);
}
void litvin::command_dict_t::executeCommand(const std::string & command, dicts_list_t & list, const std::string & dict,
                                            const std::string & str1,
                                            const std::string & str2, std::ostream & out)
{
  signature_type_2 function = dict2.at(command);
  function(list, dict, str1, str2, out);
}
void litvin::command_dict_t::executeCommand(const std::string & command, dicts_list_t & list, const std::string & dict,
                                            const std::string & str,
                                            std::ostream & out)
{
  signature_type_3 function = dict3.at(command);
  function(list, dict, str, out);
}
void litvin::command_dict_t::executeCommand(const std::string & command, dicts_list_t & list, const std::string & dict,
                                            const std::string & word, size_t num,
                                            const std::string & trans, std::ostream & out)
{
  signature_type_4 function = dict4.at(command);
  function(list, dict, word, num, trans, out);
}
void litvin::command_dict_t::executeCommand(const std::string & command, dicts_list_t & list, const std::string & dict,
                                            const std::string & word, size_t num,
                                            std::ostream & out)
{
  signature_type_5 function = dict5.at(command);
  function(list, dict, word, num, out);
}
void litvin::command_dict_t::executeCommand(const std::string & command, const command_descriptors & cmd_desc,
                                            std::ostream & out)
{
  signature_type_6 function = dict6.at(command);
  function(cmd_desc, out);
}
void litvin::command_dict_t::executeCommand(const std::string & command, const command_descriptors & cmd_desc,
                                            const std::string & cmd,
                                            std::ostream & out)
{
  signature_type_7 function = dict7.at(command);
  function(cmd_desc, cmd, out);
}
