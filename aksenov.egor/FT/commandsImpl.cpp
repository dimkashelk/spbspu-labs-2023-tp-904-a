#include "commandsImpl.h"
#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <functional>
#include <algorithm>
#include "commands.h"
namespace aksenov
{
  dictOfTranslations createDictOftranslations(std::string &, std::istream &in, dictOfDicts &, std::ostream &)
  {
    std::string word = "";
    in >> word;
    dictOfTranslations dict;
    std::vector< std::string > translations;
    while (in)
    {
      std::string translation = "";
      in >> translation;
      if (translation == ";")
      {
        break;
      }
      translations.push_back(translation);
      dict[word] = translations;
    }
    return dict;
  }

  void createDict(std::string &str, std::istream &in, dictOfDicts &dict, std::ostream &out)
  {
    while (in)
    {
      std::string name = "";
      in >> name;
      if (name == "stop")
      {
        std::cout << "dicts created" << "\n";
        break;
      }
      dictOfTranslations translations = createDictOftranslations(str, in, dict, out);
      dict[name] = translations;
    }
  }

  void outDictionaries(std::string &, std::istream &, dictOfDicts &dicts, std::ostream &out)
  {
    for (const auto &entry : dicts)
    {
      out << "Dictionary: " << entry.first << "\n";
      const dictOfTranslations &dictionary = entry.second;

      for (const auto &word_entry : dictionary)
      {
        out << "  Word: " << word_entry.first << "\n";
        out << "  Translations: ";
        const std::vector< std::string > &translations = word_entry.second;

        std::copy(translations.begin(), translations.end(), std::ostream_iterator< std::string >(out, " "));
        out << "\n";
      }
      out << "\n";
    }
  }

  void translate(std:: string &, std::istream& in, dictOfDicts& dicts, std::ostream& out)
  {
    std::string nameOfDict;
    std::string word;

    in >> nameOfDict >> word;

    auto dictIter = dicts.find(nameOfDict);
    if (dictIter == dicts.end())
    {
      out << "Dictionary '" << nameOfDict << "' not found." << std::endl;
    }
    else
    {
      const dictOfTranslations& dictionary = dictIter->second;
      auto translationIter = dictionary.find(word);
      if (translationIter != dictionary.end())
      {
        const std::vector<std::string>& translations = translationIter->second;
        out << word << " translations in dictionary " << nameOfDict << ":\n";
        std::copy(translations.begin(), translations.end(), std::ostream_iterator< std::string >(out, "- "));
      }
      else
      {
        out << "word not found";
      }
    }
  }

  void help(std::string &, std::istream &, dictOfDicts &, std::ostream &out)
  {
    out << "Commands that you are able to use:" << "\n";
    out << "1) CREATE - creates new dictionary" << "\n";
    out << "example : CREATE eng1 hello привет здравствуйте ; eng2 car машина автомобиль" << "\n";
    out << "2) OUT - creates a list of dictionaries in console" << "\n";
    out << "4) TRANSLATE - shows a translation/translations of a word" << "\n";
    out << "5) INTERSECTION - create a new dict with intersection of dictionaries, which names you have inserted" << "\n";
    out << "6) INION - unite dictionaries, which names you have inserted and create new dictionary" << "\n";
    out << "7) HELP" << "\n";
  }

  std::string AddUniqueTranslation(const std::string& translation)
  {
    return translation;
  }

  void doIntersect(std::string &, std::istream &in, dictOfDicts &dicts, std::ostream &out)
  {
    std::string newNameOfDict;
    in >> newNameOfDict;
    dictOfTranslations intersectedDict;

    while (!std::cin.eof())
    {
      std::string dictName;
      in >> dictName;
      if (dictName == "stop")
      {
        break;
      }

      auto dictIter = dicts.find(dictName);
      if (dictIter != dicts.end())
      {
        const dictOfTranslations &dictionary = dictIter->second;

        for (const auto &word_entry : dictionary)
        {
          const std::string &word = word_entry.first;
          const std::vector< std::string > &translations = word_entry.second;

          if (intersectedDict.find(word) == intersectedDict.end())
          {
            intersectedDict[word] = translations;
          }
          else
          {
            std::vector< std::string > &existingTranslations = intersectedDict[word];
            for (const std::string &translation : translations)
            {
              if (std::find(existingTranslations.begin(), existingTranslations.end(), translation) == existingTranslations.end())
              {
                existingTranslations.push_back(translation);
              }
            }
          }
        }
      }
      else
      {
        out << "Dictionary '" << dictName << "' not found." << std::endl;
      }
    }
    dicts[newNameOfDict] = intersectedDict;

    out << "New dictionary '" << newNameOfDict << "' created with intersection of dictionaries." << std::endl;
  }

  std::pair< std::string, std::vector< std::string > > TransformDictionaryEntry(const std::pair< std::string, std::vector< std::string > > &wordEntry)
  {
    return std::make_pair(wordEntry.first, wordEntry.second);
  }

  void unite(std::string &, std::istream &in, dictOfDicts &dicts, std::ostream &out)
  {
    std::string newNameOfDict;
    in >> newNameOfDict;
    dictOfTranslations unionDict;

    while (!std::cin.eof())
    {
      std::string dictName;
      in >> dictName;
      if (dictName == "stop")
      {
        break;
      }

      auto dictIter = dicts.find(dictName);
      if (dictIter != dicts.end())
      {
        const dictOfTranslations &dictionary = dictIter->second;
        std::transform(dictionary.begin(), dictionary.end(), std::inserter(unionDict, unionDict.begin()), TransformDictionaryEntry);
      }
      else
      {
        out << "Dictionary '" << dictName << "' not found." << std::endl;
      }
    }
    dicts[newNameOfDict] = unionDict;

    out << "New dictionary '" << newNameOfDict << "' created with union of dictionaries." << std::endl;
  }
}
