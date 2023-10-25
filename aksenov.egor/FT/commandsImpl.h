#ifndef COMMANDSIMPL_H
#define COMMANDSIMPL_H
#include "commands.h"
namespace aksenov
{
  void outDictionaries(std::string &, std::istream &, dictOfDicts &dicts, std::ostream &out);
  void translate(std::string &, std::istream &in, dictOfDicts &dicts, std::ostream &out);
  void help(std::string &, std::istream &, dictOfDicts &, std::ostream &out);
  void doIntersect(std::string &, std::istream &in, dictOfDicts &dicts, std::ostream &out);
  void unite(std::string &, std::istream &in, dictOfDicts &dicts, std::ostream &out);
  void addHistory(std::string &command, std::istream &, dictOfDicts &, std::ostream &);
  void showHistory(std::string &, std::istream &, dictOfDicts &, std::ostream &out);
}
#endif

