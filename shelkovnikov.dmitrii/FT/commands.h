#ifndef FT_COMMANDS_H
#define FT_COMMANDS_H
#include <map>
#include <string>
#include <ostream>
using frequency_dict = std::map< std::string, std::map< std::string, size_t > >;
using text_dict = std::map< std::string, std::string >;
using c_str = const std::string &;
namespace dimkashelk
{
  void load(text_dict &dict, c_str filename);
  void analyze(frequency_dict &dict, text_dict &text, c_str filename);
  void exportToFile(frequency_dict &dict, c_str dictname, c_str filename);
  void exportWithText(frequency_dict &dict, c_str dictname, c_str filename);
  void printWord(frequency_dict &dict, c_str dictname, c_str word, std::ostream &out);
  void print(frequency_dict &dict, c_str filename);
  void deleteWord(frequency_dict &dict, c_str dictname, c_str word);
  void deleteDict(frequency_dict &dict, c_str filename);
  void remove(text_dict &dict, c_str filename);
  void getTop(frequency_dict, c_str dictname, size_t count, std::ostream &out);
  void getComplement(frequency_dict &dict, c_str newdata, c_str dict1, c_str dict2);
  void getIntersect(frequency_dict &dict, c_str newdata, c_str dict1, c_str dict2);
  void getUnion(frequency_dict &dict, c_str newdata, c_str dict1, c_str dict2);
  void help(std::ostream &out);
}
#endif
