#include "auxiliary_fns.hpp"
litvin::command_dict_t::command_dict_t()
{
  dict1.insert({"search", searchWord});
  dict1.insert({"print", printDict});
  dict1.insert({"delete", deleteDict});
  dict3.insert({"new", createNewDict});
  dict1.insert({"insert", insertWordTranslation});
  dict1.insert({"add", addWordTranslation});
  dict1.insert({"intersect", intersectDictionaries});
  dict1.insert({"union", unionDictionaries});
  dict1.insert({"difference", subtractDictionaries});
  dict1.insert({"remove", removeWordFromDict});
  dict1.insert({"printl", printDictByLetter});
  dict1.insert({"edit", editWordTranslation});
  dict1.insert({"erase", eraseWordTranslation});
  dict2.insert({"help", help});
  dict2.insert({"man", man});
}
litvin::command_descriptors litvin::createCommandDescriptorsDict()
{
  command_descriptors dict;
  dict.insert({"search", "searches word translation in all available dictionaries"});
  dict.insert({"print", "prints all dictionary with its words and their translations"});
  dict.insert({"delete", "deletes dictionary with name, equal to argument"});
  dict.insert({"new", "creates new empty dictionary with name, equal to argument"});
  dict.insert({"insert", "inserts the word to the dict with translation"});
  dict.insert({"add", "adds new translation to the word"});
  dict.insert({"intersect", "creates a dict, which is intersection of two already existing dicts"});
  dict.insert({"union", "creates a dict, which is union of two already existing dicts"});
  dict.insert({"difference", "creates a dict, which is subtraction of two already existing dicts"});
  dict.insert({"remove", "removes the word from dictionary with its translation list"});
  dict.insert({"printl", "prints words and their translations from dict starting by the letter-parameter"});
  dict.insert({"edit", "edits the word translation by number-parameter"});
  dict.insert({"erase", "erases the word translation by number-parameter"});
  dict.insert({"man", "gives info about requested command"});
  dict.insert({"help", "gives info about all available commands"});
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
    out << "This command does not exists, see 'help'\n";
  }
}
void litvin::help(const command_descriptors & cmd_desc, std::ostream & out, std::istream & in)
{
  for (const auto & desc: cmd_desc)
  {
    out << desc.first << ": " << desc.second << '\n';
  }
}
void litvin::command_dict_t::executeCommand(const std::string & command, dicts_list_t & list, std::ostream & out,
                                            std::istream & in) const
{
  signature_type_1 function = dict1.at(command);
  function(list, out, in);
}
void litvin::command_dict_t::executeCommand(const std::string & command, const command_descriptors & cmd_desc,
                                            std::ostream & out, std::istream & in) const
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
  if (cmd == "new")
  {
    std::string dict_name = " ";
    in >> dict_name;
    cmd_d.executeCommand(cmd, list, dict_name, out);
  }
  else
  {
    throw std::invalid_argument("invalid command");
  }
}
