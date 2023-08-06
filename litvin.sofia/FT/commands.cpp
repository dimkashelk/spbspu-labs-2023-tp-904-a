#include "commands.hpp"
#include "dict.hpp"
bool litvin::findDict(const dicts_list_t & list, const std::string & dict_name)
{
  try
  {
    list.dict_list.at(dict_name);
  } catch (const std::out_of_range &)
  {
    return false;
  }
  return true;
}
litvin::translations * litvin::findWordTranslation(dicts_list_t & list, const std::string & dict_name,
                                                   const std::string & word)
{
  dict_t & dictionary = list.dict_list[dict_name];
  try
  {
    return &dictionary.at(word);
  } catch (const std::out_of_range &)
  {
    return nullptr;
  }
}
void litvin::createNewDict(dicts_list_t & list, const std::string & dict_name, std::ostream & out)
{
  if (findDict(list, dict_name))
  {
    out << "A dictionary with this name already exists\n";
  }
  else
  {
    dict_t new_dict;
    list.dict_list.insert(std::pair< std::string, dict_t >(dict_name, new_dict));
    out << "Created new dictionary: " << dict_name << '\n';
  }
}
void litvin::deleteDict(dicts_list_t & list, const std::string & dict_name, std::ostream & out)
{
  if (findDict(list, dict_name))
  {
    list.dict_list.erase(dict_name);
    out << "A dictionary " << dict_name << " has been deleted\n";
  }
  else
  {
    out << "A dictionary with this name does not exists\n";
  }
}
void litvin::insertWordTranslation(dicts_list_t & list, const std::string & dict_name, const std::string & word,
                                   const std::string & trans, std::ostream & out)
{
  if (findDict(list, dict_name))
  {
    translations * trans_v = findWordTranslation(list, dict_name, word);
    if (trans_v != nullptr)
    {
      trans_v->push_back(trans);
    }
    else
    {
      dict_t & dictionary = list.dict_list[dict_name];
      translations vector_of_translations;
      vector_of_translations.push_back(trans);
      dictionary.insert(std::pair< std::string, std::vector< std::string > >(word, vector_of_translations));
    }
  }
  else
  {
    out << "A dictionary with this name does not exists\n";
  }
}
void litvin::removeWordFromDict(dicts_list_t & list, const std::string & dict_name, const std::string & word,
                                std::ostream & out)
{
  if (findDict(list, dict_name))
  {
    translations * trans_v = findWordTranslation(list, dict_name, word);
    if(trans_v != nullptr){
      list.dict_list[dict_name].erase(word);
    }
    else{
      out << "There is no " << word << " translation in " << dict_name << "dictionary\n";
    }
  }
  else
  {
    out << "A dictionary with this name does not exists\n";
  }
}
