#ifndef COMMANDS_H
#define COMMANDS_H

#include <functional>
#include "minorCommands.h"

namespace aristarkhov
{
  void processCommand(dictionaryOfNames& dictionaries, const std::string cmd, std::istream& in, std::ostream& out);
  using mapOfFunctions =
    std::map< std::string,
    std::function< void(dictionaryOfNames&, std::istream&, std::ostream&) > >;
}
#endif
