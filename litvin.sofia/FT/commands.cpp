#include "commands.hpp"
#include "dict.hpp"
void litvin::createNewDict(dicts_list_t & list, const std::string & dict_name, std::ostream & out)
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
void litvin::deleteDict(dicts_list_t & list, const std::string & dict_name, std::ostream & out)
{
  try
  {
    list.dict_list.at(dict_name);
    list.dict_list.erase(dict_name);
    out << "A dictionary " << dict_name << " has been deleted\n";
  }
  catch (const std::out_of_range &)
  {
    out << "A dictionary with this name does not exists\n";
  }
}
void litvin::insertWordTranslation(dicts_list_t & list, const std::string & dict, const std::string & word,
                                   const std::string & trans, std::ostream & out)
{
  try
  {
    list.dict_list.at(dict);
  } catch (const std::out_of_range &)
  {
    out << "A dictionary with this name does not exists\n";
    return;
  }
  try
  {
    dict_t & dictionary = list.dict_list[dict];
    translations & trans_v = dictionary.at(word);
    trans_v.push_back(trans);
  } catch (const std::out_of_range &)
  {
    dict_t & dictionary = list.dict_list[dict];
    translations vector_of_translations;
    vector_of_translations.push_back(trans);
    dictionary.insert(std::pair< std::string, std::vector< std::string > >(word, vector_of_translations));
  }
}
