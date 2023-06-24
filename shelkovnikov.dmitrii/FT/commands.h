#ifndef FT_COMMANDS_H
#define FT_COMMANDS_H
#include <map>
#include <string>
using frequency_dict = std::map< std::string, std::map< std::string, size_t > >;
using text_dict = std::map< std::string, std::string >;
namespace dimkashelk
{
  void load(text_dict &dict, const std::string &filename);
  void analyze(frequency_dict &dict, const std::string &filename);
  void exportToFile(frequency_dict &dict, const std::string &dictname, const std::string &filename);
  void exportWithText(frequency_dict &dict, const std::string &dictname, const std::string &filename);
  void printWord(frequency_dict &dict, const std::string &dictname, const std::string &word, std::ostream &out);
}
#endif
