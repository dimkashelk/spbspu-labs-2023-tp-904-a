#include "auxiliary_commands.h"
#include <limits>

namespace shestakov
{
  void printInvalidCommand(std::ostream &out)
  {
    out << "<INVALID COMMAND>";
  }
  void printInvalidArgument(std::ostream &out)
  {
    out << "<INVALID ARGUMENT>";
  }
  void skipUntilNewLine(std::istream &in)
  {
    in.clear();
    auto maxstream = std::numeric_limits<std::streamsize>::max();
    in.ignore(maxstream, '\n');
  }
  bool searchDict(const my_map &dictionaries, const std::string &dict_name)
  {
    return dictionaries.find(dict_name) != dictionaries.end();
  }
}
