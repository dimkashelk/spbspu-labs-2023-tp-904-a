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
