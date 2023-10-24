#ifndef DICTIONARYCOMMANDS_H
#define DICTIONARYCOMMANDS_H

#include "minorCommands.hpp"

namespace aristarkhov
{

  void createDictionary(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out);
  void deleteDictionary(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out);
  void readTextIntoDictionary(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out);
  void readFile(dictionaryOfNames& dictionaries, std::istream& in, std::ostream& out);

}

#endif
