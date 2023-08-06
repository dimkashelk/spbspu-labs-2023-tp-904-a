#include "commands.hpp"
#include "dict.hpp"
void litvin::createNewDict(list_of_dicts_t & list, const std::string & dict_name, std::ostream & out)
{
  try
  {
    list.dict_list.at(dict_name);
    out << "A dictionary with this name already exists\n";
  } catch (const std::out_of_range &)
  {
    dict_t new_dict;
    list.dict_list.insert(std::pair< std::string, dict_t >(dict_name, new_dict));
    out << "Created new dictionary: " << dict_name << '\n';
  }
}
void litvin::deleteDict(list_of_dicts_t & list, const std::string & dict_name, std::ostream & out)
{
  try{
    list.dict_list.at(dict_name);
    list.dict_list.erase(dict_name);
    out << "A dictionary " << dict_name << " has been deleted\n";
  }
  catch (const std::out_of_range &){
    out << "A dictionary with this name does not exists\n";
  }
}