#ifndef FT_COMMANDS_H
#define FT_COMMANDS_H
#include <map>
#include <string>
#include <ostream>
using frequency_dict = std::map< std::string, std::map< std::string, size_t > >;
using text_dict = std::map< std::string, std::string >;
using all_data = std::pair< frequency_dict, text_dict >;
using c_s = const std::string &;
namespace dimkashelk
{
  void load(all_data &dict, c_s filename);
  void analyze(all_data &dict, c_s filename);
  void exportToFile(frequency_dict &dict, c_s dictname, c_s filename);
  void exportWithText(frequency_dict &dict, text_dict &dictText, c_s dictname, c_s filename);
  void printWord(frequency_dict &dict, c_s dictname, c_s word, std::ostream &out);
  void print(frequency_dict &dict, c_s filename);
  void deleteWord(frequency_dict &dict, c_s dictname, c_s word);
  void deleteDict(frequency_dict &dict, c_s filename);
  void remove(text_dict &dict, c_s filename);
  void getTop(frequency_dict, c_s dictname, size_t count, std::ostream &out);
  void getComplement(frequency_dict &dict, c_s newdata, c_s dict1, c_s dict2);
  void getIntersect(frequency_dict &dict, c_s newdata, c_s dict1, c_s dict2);
  void getUnion(frequency_dict &dict, c_s newdata, c_s dict1, c_s dict2);
  void help(std::ostream &out);
}
#endif
