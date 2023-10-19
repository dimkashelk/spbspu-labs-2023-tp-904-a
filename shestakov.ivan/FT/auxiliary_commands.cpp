#include "auxiliary_commands.h"
#include <limits>

namespace shestakov
{
  void printError(std::ostream &out)
  {
    out << "<INVALID COMMAND>\n";
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
