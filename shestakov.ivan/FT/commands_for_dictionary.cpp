#include "commands_for_dictionary.h"
#include <algorithm>
#include <fstream>
#include <numeric>
#include <vector>
#include "auxiliary_commands.h"
#include "dictionary.h"

namespace shestakov
{
  void addWord(Dictionary &dictionary, std::istream &in, std::ostream &out)
  {
    std::string word = "";
    in >> word;
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
    if (searchWrd(dictionary, word))
    {
      ++dictionary.dict[word];
      out << "The counter of word \"" << word << "\" has been increased.\n";
      return;
    }
    dictionary.dict[word] = 1;
    out << "Word \"" << word << "\" has been added to the dictionary.\n";
  }
  void searchWord(const Dictionary &dictionary, std::istream &in, std::ostream &out)
  {
    std::string word = "";
    in >> word;
    if (searchWrd(dictionary, word))
    {
      out << "Word \"" << word << "\" exist in dictionary.\n";
      return;
    }
    out << "Word \"" << word << "\" does not exist in dictionary.\n";
  }
  void countWords(const Dictionary &dictionary, std::istream &in, std::ostream &out)
  {
    if (!dictionary.dict.size())
    {
      out << "Dictionary is empty.\n";
      return;
    }
    out << "Count of words: " << dictionary.dict.size() << '\n';
  }
  void countWordsWithFreq(const Dictionary &dictionary, std::istream &in, std::ostream &out)
  {
    if (!dictionary.dict.size())
    {
      out << "Dictionary is empty.\n";
      return;
    }
    std::vector< size_t > freq(dictionary.dict.size());
    std::transform(dictionary.dict.cbegin(), dictionary.dict.cend(), freq.begin(), countFreq);
    out << "Count of words with frequency: " << std::accumulate(freq.begin(), freq.end(), 0.0) << '\n';
  }
  void printThreeMostCommonWords(const Dictionary &dictionary, std::istream &in, std::ostream &out)
  {
    if (!dictionary.dict.size())
    {
      out << "Dictionary is empty.\n";
      return;
    }
    std::vector< std::pair< size_t, std::string > > freq(dictionary.dict.size());
    std::transform(dictionary.dict.cbegin(), dictionary.dict.cend(), freq.begin(), returnSet);
    std::sort(freq.begin(), freq.end(), compSet);
    std::reverse(freq.begin(), freq.end());
    out << freq[0].second;
    for (size_t i = 1; i < freq.size() && i < 3; ++i)
    {
      out << ", " << freq[i].second;
    }
    out << " most common words in dictionary\n";
  }
  void deleteWord(Dictionary &dictionary, std::istream &in, std::ostream &out)
  {
    if (!dictionary.dict.size())
    {
      out << "Dictionary is empty.\n";
      skipUntilNewLine(in);
      return;
    }
    std::string word = "";
    in >> word;
    if (!searchWrd(dictionary, word))
    {
      out << "Word does not exist.\n";
      return;
    }
    auto place = dictionary.dict.find(word);
    dictionary.dict.erase(place);
    out << "Word \"" << word << "\" has been deleted.\n";
  }
  void saveDictionary(const Dictionary &dictionary, std::istream &in, std::ostream &out)
  {
    std::string file_name = "";
    out << "Enter file name:\n";
    in >> file_name;
    file_name = "../" + file_name;
    std::ofstream file(file_name);
    std::string str = "";
    size_t size = 0;
    for (const auto &pair : dictionary.dict)
    {
      size = 50 - pair.first.length();
      str = pair.first + std::string(size, '.');
      file << str << pair.second << '\n';
    }
    file.close();
    out << "Dictionary is written to file.\n";
  }
}
