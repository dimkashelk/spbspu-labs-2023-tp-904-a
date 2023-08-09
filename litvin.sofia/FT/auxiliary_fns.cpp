#include "auxiliary_fns.hpp"
litvin::command_dict_t::command_dict_t()
{
  dict1.insert({"SEARCH", searchWord});
  dict1.insert({"PRINT", printDict});
  dict1.insert({"DELETE", deleteDict});
  dict3.insert({"NEW", createNewDict});
  dict1.insert({"INSERT", insertWordTranslation});
  dict1.insert({"ADD", addWordTranslation});
  dict1.insert({"INTERSECT", intersectDictionaries});
  dict1.insert({"UNION", unionDictionaries});
  dict1.insert({"DIFFERENCE", subtractDictionaries});
  dict1.insert({"REMOVE", removeWordFromDict});
  dict1.insert({"PRINTL", printDictByLetter});
  dict1.insert({"EDIT", editWordTranslation});
  dict1.insert({"ERASE", eraseWordTranslation});
  dict2.insert({"HELP", help});
  dict2.insert({"MAN", man});
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
void litvin::man(const command_descriptors & cmd_desc, std::ostream & out, std::istream & in)
{
  try
  {
    std::string command = " ";
    in >> command;
    out << cmd_desc.at(command) << '\n';
  }
  catch (const std::out_of_range &)
  {
    out << "This command does not exists, see 'HELP'\n";
  }
}
void litvin::help(const command_descriptors & cmd_desc, std::ostream & out, std::istream & in)
{
  for (const auto & desc: cmd_desc)
  {
    out << desc.first << " " << desc.second << '\n';
  }
}
void litvin::command_dict_t::executeCommand(const std::string & command, dicts_list_t & list, std::ostream & out,
                                            std::istream & in) const
{
  signature_type_1 function = dict1.at(command);
  function(list, out, in);
}
void litvin::command_dict_t::executeCommand(const std::string & command, const command_descriptors & cmd_desc,
                                            std::ostream & out,
                                            std::istream & in) const
{
  signature_type_2 function = dict2.at(command);
  function(cmd_desc, out, in);
}
void litvin::command_dict_t::executeCommand(const std::string & command, dicts_list_t & list, const std::string & dict,
                                            std::ostream & out) const
{
  signature_type_3 function = dict3.at(command);
  function(list, dict, out);
}
std::string litvin::inputCommand(std::istream & in)
{
  std::string command_name = " ";
  in >> command_name;
  if (!in)
  {
    throw std::runtime_error("End of input");
  }
  return command_name;
}
void litvin::runCommand(const command_dict_t & cmd_d, dicts_list_t & list, const command_descriptors & desc_d,
                        const std::string & cmd, std::ostream & out, std::istream & in)
{
  try
  {
    cmd_d.executeCommand(cmd, list, out, in);
    return;
  } catch (const std::out_of_range &)
  {
  }
  try
  {
    cmd_d.executeCommand(cmd, desc_d, out, in);
    return;
  } catch (const std::out_of_range &)
  {
  }
  std::string dict_name = " ";
  in >> dict_name;
  cmd_d.executeCommand(cmd, list, dict_name, out);
}
