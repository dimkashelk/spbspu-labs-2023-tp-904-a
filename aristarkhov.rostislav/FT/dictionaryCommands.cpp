#include "dictionaryCommands.h"

#include <string>
#include <fstream>
#include <algorithm>

namespace aristarkhov
{
  void createDictionary(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string dict_name = "";
    in >> dict_name;
    Dictionary dict;
    if (!searchDict(dictionaries, dict_name))
    {
      dictionaries.emplace(dict_name, dict);
      out << "Dictionary \"" << dict_name << "\" has been created.\n";
    }
    else
    {
      out << "Dictionary \"" << dict_name << "\" already exists.\n";
    }
  }

  void deleteDictionary(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string dict_name = "";
    in >> dict_name;

    validateDictExists(dictionaries, dict_name);

    auto place = dictionaries.find(dict_name);
    dictionaries.erase(place);
    out << "Dictionary \"" << dict_name << "\" was deleted.\n";
  }

  void readTextIntoDictionary(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string dict_name;
    in >> dict_name;

    validateDictExists(dictionaries, dict_name);

    std::string line;
    in.ignore();
    std::getline(in, line);

    const std::string delimiters = " \n\r\t,.;:!?'\"-";

    size_t start = line.find_first_not_of(delimiters);
    size_t end;

    while (start != std::string::npos)
    {
      end = line.find_first_of(delimiters, start + 1);
      if (end == std::string::npos)
      {
        end = line.length();
      }

      std::string word = line.substr(start, end - start);

      word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
      std::transform(word.begin(), word.end(), word.begin(), tolower);
      ++dictionaries[dict_name][word];

      start = line.find_first_not_of(delimiters, end + 1);
    }

    out << "Added text to dictionary \"" << dict_name << "\".\n";
  }

  void readFile(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string dict_name = "";
    in >> dict_name;

    validateDictExists(dictionaries, dict_name);

    std::string file_name = "";
    in >> file_name;
    std::ifstream file(file_name);
    if (!file.is_open())
    {
      throw std::runtime_error("File didn't open");
    }

    std::string word;
    while (file >> word)
    {
      word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
      std::transform(word.begin(), word.end(), word.begin(), tolower);
      ++dictionaries[dict_name][word];
    }

    out << "File \"" << file_name << "\" has been read into the dictionary \"" << dict_name << "\".\n";
  }

  void findWord(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string dict_name = "";
    in >> dict_name;

    validateDictExists(dictionaries, dict_name);

    std::string word = "";
    in >> word;
    if (searchWrd(dictionaries[dict_name], word))
    {
      out << "Word \"" << word << "\" exists in dictionary \"" << dict_name << "\" with frequency "
        << dictionaries[dict_name][word] << ".\n";
    }
    else
    {
      dictionaries[dict_name][word] = 1;
      out << "Word \"" << word << "\" does not exist in dictionary \"" << dict_name << "\".\n";
    }
  }

  void deleteWord(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string dict_name = "";
    in >> dict_name;

    validateDictExists(dictionaries, dict_name);

    std::string word = "";
    in >> word;
    if (searchWrd(dictionaries[dict_name], word))
    {
      dictionaries[dict_name].erase(word);
      out << "Word \"" << word << "\" has been deleted from dictionary \"" << dict_name << "\".\n";
    }
    else
    {
      out << "Word \"" << word << "\" does not exist in dictionary \"" << dict_name << "\".\n";
    }
  }

  void getWordCount(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string dict_name = "";
    in >> dict_name;

    validateDictExists(dictionaries, dict_name);

    out << "Count of words in dictionary \"" << dict_name << "\" is " << dictionaries[dict_name].size() << ".\n";
  }

  void getFrequency(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string dict_name = "";
    in >> dict_name;

    validateDictExists(dictionaries, dict_name);

    std::string word = "";
    in >> word;
    if (searchWrd(dictionaries[dict_name], word))
    {
      out << "Word \"" << word << "\" has frequency " << dictionaries[dict_name][word] << " in dictionary \""
        << dict_name << "\".\n";
    }
    else
    {
      out << "Word \"" << word << "\" does not exist in dictionary \"" << dict_name << "\".\n";
    }
  }

  void getMostUseWord(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string dict_name = "";
    in >> dict_name;

    validateDictExists(dictionaries, dict_name);

    size_t n;
    in >> n;

    std::vector< std::pair< std::string, size_t > > items(dictionaries[dict_name].begin(),
      dictionaries[dict_name].end());
    std::sort(items.begin(), items.end(), compareFrequency);

    out << "Most used words in dictionary \"" << dict_name << "\":\n";
    for (size_t i = 0; i < std::min(n, items.size()); ++i)
    {
      out << items[i].first << " with frequency of " << items[i].second << "\n";
    }
  }

  void clearDictionary(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string dict_name = "";
    in >> dict_name;

    validateDictExists(dictionaries, dict_name);

    dictionaries[dict_name].clear();
    out << "All words in the dictionary \"" << dict_name << "\" have been deleted.\n";
  }

  void removeText(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out)
  {
    std::string text = "";
    std::getline(in, text);
    for (auto& dict : dictionaries)
    {
      size_t start = 0;
      while ((start = text.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", start)) !=
        std::string::npos)
      {
        size_t end = text.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", start);
        std::string word = text.substr(start, end - start);
        word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        if (searchWrd(dict.second, word))
        {
          if (dict.second[word] > 1)
          {
            dict.second[word]--;
            out << "Decreased the counter for word \"" << word << "\" in the \"" << dict.first << "\" dictionary.\n";
          }
          else
          {
            dict.second.erase(word);
            out << "Word \"" << word << "\" has been deleted from dictionary \"" << dict.first << "\".\n";
          }
        }
        start = end;
      }
    }
  }

}
