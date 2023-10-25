#ifndef COMMANDSIMPL_H
#define COMMANDSIMPL_H
#include "commands.h"
namespace aksenov
{
  dictOfTranslations createDictOftranslations(std::string &, std::istream &in, dictOfDicts &, std::ostream &);
  void createDict(std::string &, std::istream &in, dictOfDicts &dict, std::ostream &);
  void outDictionaries(std::string &, std::istream &, dictOfDicts &dicts, std::ostream &out);
  void translate(std::string &, std::istream &in, dictOfDicts &dicts, std::ostream &out);
  void help(std::string &, std::istream &, dictOfDicts &, std::ostream &out);
  void doIntersect(std::string &, std::istream &in, dictOfDicts &dicts, std::ostream &out);
  void unite(std::string &, std::istream &in, dictOfDicts &dicts, std::ostream &out);
}
#endif

