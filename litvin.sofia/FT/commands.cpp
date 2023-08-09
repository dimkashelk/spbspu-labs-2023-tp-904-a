#include "commands.hpp"
#include <algorithm>
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
    out << "A dictionary " << dict_name << " already exists\n";
  }
  else
  {
    dict_t new_dict;
    list.dict_list.insert(std::pair< std::string, dict_t >(dict_name, new_dict));
    out << "Created new dictionary: " << dict_name << '\n';
  }
}
void litvin::deleteDict(dicts_list_t & list, std::ostream & out, std::istream & in)
{
  std::string dict_name = " ";
  in >> dict_name;
  if (!in)
  {
    throw std::invalid_argument("invalid command");
  }
  if (findDict(list, dict_name))
  {
    list.dict_list.erase(dict_name);
    out << "A dictionary " << dict_name << " has been deleted\n";
  }
  else
  {
    out << "A dictionary " << dict_name << " does not exists\n";
  }
}
void litvin::insertWordTranslation(dicts_list_t & list, std::ostream & out, std::istream & in)
{
  std::string dict_name = " ";
  in >> dict_name;
  std::string word = " ";
  in >> word;
  if (!in)
  {
    throw std::invalid_argument("invalid command");
  }
  std::string trans = " ";
  getline(in, trans);
  if (trans == "")
  {
    throw std::invalid_argument("invalid command");
  }
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
    out << "A dictionary " << dict_name << " does not exists\n";
  }
}
void litvin::removeWordFromDict(dicts_list_t & list, std::ostream & out, std::istream & in)
{
  std::string dict_name = " ";
  in >> dict_name;
  std::string word = " ";
  in >> word;
  if (!in)
  {
    throw std::invalid_argument("invalid command");
  }
  if (findDict(list, dict_name))
  {
    translations * trans_v = findWordTranslation(list, dict_name, word);
    if (trans_v != nullptr)
    {
      list.dict_list[dict_name].erase(word);
    }
    else
    {
      out << "There is no " << word << " translation in " << dict_name << " dictionary\n";
    }
  }
  else
  {
    out << "A dictionary " << dict_name << " does not exists\n";
  }
}
void litvin::editWordTranslation(dicts_list_t & list, std::ostream & out, std::istream & in)
{
  std::string dict_name = " ";
  in >> dict_name;
  std::string word = " ";
  in >> word;
  size_t num_of_translation = 0;
  in >> num_of_translation;
  std::string new_translation = " ";
  getline(in, new_translation);
  if (!in)
  {
    throw std::invalid_argument("invalid command");
  }
  if (findDict(list, dict_name))
  {
    translations * trans_v = findWordTranslation(list, dict_name, word);
    if (trans_v != nullptr)
    {
      try
      {
        trans_v->at(num_of_translation - 1) = new_translation;
      } catch (const std::out_of_range &)
      {
        out << "There is no translation in " << dict_name << " with number " << num_of_translation << '\n';
      }
    }
    else
    {
      out << "Word " << word << " does not belongs to " << dict_name << " dictionary\n";
    }
  }
  else
  {
    out << "A dictionary " << dict_name << " does not exists\n";
  }
}
void litvin::addWordTranslation(dicts_list_t & list, std::ostream & out, std::istream & in)
{
  std::string dict_name = " ";
  in >> dict_name;
  std::string word = " ";
  in >> word;
  std::string new_translation = " ";
  getline(in, new_translation);
  if (!in)
  {
    throw std::invalid_argument("invalid command");
  }
  if (findDict(list, dict_name))
  {
    translations * trans_v = findWordTranslation(list, dict_name, word);
    if (trans_v != nullptr)
    {
      trans_v->push_back(new_translation);
    }
    else
    {
      out << "Word " << word << " does not belongs to " << dict_name << " dictionary\n";
    }
  }
  else
  {
    out << "A dictionary " << dict_name << " does not exists\n";
  }
}
void litvin::eraseWordTranslation(dicts_list_t & list, std::ostream & out, std::istream & in)
{
  std::string dict_name = " ";
  in >> dict_name;
  std::string word = " ";
  in >> word;
  size_t num_of_translation = 0;
  in >> num_of_translation;
  if (!in)
  {
    throw std::invalid_argument("invalid command");
  }
  if (findDict(list, dict_name))
  {
    translations * trans_v = findWordTranslation(list, dict_name, word);
    if (trans_v != nullptr)
    {
      if (num_of_translation <= trans_v->size() && num_of_translation > 0)
      {
        trans_v->erase(trans_v->begin() + num_of_translation - 1);
      }
      else
      {
        out << "There is no translation in " << dict_name << " with number " << num_of_translation << '\n';
      }
    }
    else
    {
      out << "Word " << word << " does not belongs to " << dict_name << " dictionary\n";
    }
  }
  else
  {
    out << "A dictionary " << dict_name << " does not exists\n";
  }
}
void litvin::printDict(dicts_list_t & list, std::ostream & out, std::istream & in)
{
  std::string dict_name = " ";
  in >> dict_name;
  if (!in)
  {
    throw std::invalid_argument("invalid command");
  }
  if (findDict(list, dict_name))
  {
    const dict_t & dictionary = list.dict_list[dict_name];
    for (const auto & entry: dictionary)
    {
      const std::string & word = entry.first;
      const translations & trans_list = entry.second;
      out << word << ":\n";
      size_t translation_number = 1;
      for (const std::string & translation: trans_list)
      {
        out << "  " << translation_number << ". " << translation << "\n";
        translation_number++;
      }
    }
  }
  else
  {
    out << "A dictionary " << dict_name << " does not exists\n";
  }
}
void litvin::printDictByLetter(dicts_list_t & list, std::ostream & out, std::istream & in)
{
  std::string dict_name = " ";
  in >> dict_name;
  char letter = ' ';
  in >> letter;
  if (!in)
  {
    throw std::invalid_argument("invalid command");
  }
  if (findDict(list, dict_name))
  {
    const dict_t & dictionary = list.dict_list[dict_name];
    size_t quantity_of_words = 0;
    for (const auto & entry: dictionary)
    {
      const std::string & word = entry.first;
      const translations & trans_list = entry.second;
      if (word.front() == letter)
      {
        quantity_of_words++;
        out << word << ":\n";
        size_t translation_number = 1;
        for (const std::string & translation: trans_list)
        {
          out << "  " << translation_number << ". " << translation << "\n";
          translation_number++;
        }
      }
    }
    if (!quantity_of_words)
    {
      out << "No words found for this letter\n";
    }
  }
  else
  {
    out << "A dictionary " << dict_name << " does not exists\n";
  }
}
void litvin::searchWord(dicts_list_t & list, std::ostream & out, std::istream & in)
{
  std::string word = " ";
  in >> word;
  if (!in)
  {
    throw std::invalid_argument("invalid command");
  }
  size_t quantity = 0;
  for (const auto & dict: list.dict_list)
  {
    const std::string & dict_name = dict.first;
    const dict_t & dictionary = dict.second;
    if (dictionary.count(word))
    {
      quantity++;
      const translations & trans_list = dictionary.at(word);
      out << dict_name << ":\n";
      size_t translation_number = 1;
      for (const std::string & translation: trans_list)
      {
        out << "  " << translation_number << ". " << translation << "\n";
        translation_number++;
      }
    }
  }
  if (quantity == 0)
  {
    out << word << " is not found\n";
  }
}
void litvin::unionDictionaries(dicts_list_t & list, std::ostream & out, std::istream & in)
{
  std::string dict1 = " ";
  std::string dict2 = " ";
  std::string dict3 = " ";
  in >> dict1 >> dict2 >> dict3;
  if (!in)
  {
    throw std::invalid_argument("invalid command");
  }
  if (findDict(list, dict1))
  {
    if (findDict(list, dict2))
    {
      createNewDict(list, dict3, out);
      dict_t & dictionary1 = list.dict_list[dict1];
      dict_t & dictionary2 = list.dict_list[dict2];
      dict_t & dictionary3 = list.dict_list[dict3];
      for (const auto & element: dictionary1)
      {
        const std::string & word = element.first;
        const translations & trans_list = element.second;
        dictionary3[word] = trans_list;
      }
      for (const auto & element: dictionary2)
      {
        const std::string & word = element.first;
        const translations & trans_list = element.second;
        for (const auto & trans: trans_list)
        {
          if (std::find(dictionary3[word].begin(), dictionary3[word].end(), trans) == dictionary3[word].end())
          {
            dictionary3[word].push_back(trans);
          }
        }
      }
    }
    else
    {
      out << "A dictionary " << dict2 << " does not exists\n";
    }
  }
  else
  {
    out << "A dictionary " << dict1 << " does not exists\n";
  }
}
void litvin::intersectDictionaries(dicts_list_t & list, std::ostream & out, std::istream & in)
{
  std::string dict1 = " ";
  std::string dict2 = " ";
  std::string dict3 = " ";
  in >> dict1 >> dict2 >> dict3;
  if (!in)
  {
    throw std::invalid_argument("invalid command");
  }
  if (findDict(list, dict1))
  {
    if (findDict(list, dict2))
    {
      createNewDict(list, dict3, out);
      dict_t & dictionary1 = list.dict_list[dict1];
      dict_t & dictionary2 = list.dict_list[dict2];
      dict_t & dictionary3 = list.dict_list[dict3];
      for (const auto & element: dictionary1)
      {
        const std::string & word = element.first;
        const translations & translist1 = element.second;
        if (dictionary2.count(word))
        {
          const translations & translist2 = dictionary2.at(word);
          translations combinedtranslations;
          combinedtranslations.insert(combinedtranslations.end(), translist1.begin(), translist1.end());
          for (const auto & translation: translist2)
          {
            if (std::find(combinedtranslations.begin(), combinedtranslations.end(), translation) ==
                combinedtranslations.end())
            {
              combinedtranslations.push_back(translation);
            }
          }
          dictionary3[word] = combinedtranslations;
        }
      }
    }
    else
    {
      out << "A dictionary " << dict2 << " does not exist\n";
    }
  }
  else
  {
    out << "A dictionary " << dict1 << " does not exist\n";
  }
}
void litvin::subtractDictionaries(dicts_list_t & list, std::ostream & out, std::istream & in)
{
  std::string dict1 = " ";
  std::string dict2 = " ";
  std::string dict3 = " ";
  in >> dict1 >> dict2 >> dict3;
  if (!in)
  {
    throw std::invalid_argument("invalid command");
  }
  if (findDict(list, dict1))
  {
    if (findDict(list, dict2))
    {
      createNewDict(list, dict3, out);
      dict_t & dictionary1 = list.dict_list[dict1];
      dict_t & dictionary2 = list.dict_list[dict2];
      dict_t & dictionary3 = list.dict_list[dict3];
      for (const auto & entry: dictionary1)
      {
        const std::string & word = entry.first;
        if (dictionary2.count(word) == 0)
        {
          const translations & trans_list_1 = entry.second;
          dictionary3[word] = trans_list_1;
        }
      }
    }
    else
    {
      out << "A dictionary " << dict2 << " does not exists\n";
    }
  }
  else
  {
    out << "A dictionary " << dict1 << " does not exists\n";
  }
}
