#ifndef FT_COMMANDS_H
#define FT_COMMANDS_H
#include <map>
#include <string>
using frequency_dict = std::map< std::string, size_t >;
using text_dict = std::map< std::string, std::string >;
namespace dimkashelk
{
  void load(text_dict &dict, std::string filename);
}
#endif
