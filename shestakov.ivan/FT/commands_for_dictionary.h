#ifndef UNTITLED4_COMMANDS_FOR_DICTIONARY_H
#define UNTITLED4_COMMANDS_FOR_DICTIONARY_H
#include <iostream>
#include "dictionary.h"

namespace shestakov
{
  void addWord(Dictionary &dictionary, std::istream &in, std::ostream &out);
  void searchWord(const Dictionary &dictionary, std::istream &in, std::ostream &out);
  void countWords(const Dictionary &dictionary, std::istream &in, std::ostream &out);
  void countWordsWithFreq(const Dictionary &dictionary, std::istream &in, std::ostream &out);
  void printThreeMostCommonWords(const Dictionary &dictionary, std::istream &in, std::ostream &out);
  void deleteWord(Dictionary &dictionary, std::istream &in, std::ostream &out);
  void saveDictionary(const Dictionary &dictionary, std::istream &in, std::ostream &out);
}
#endif
