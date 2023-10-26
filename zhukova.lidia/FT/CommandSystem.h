#ifndef FT_COMMANDSYSTEM_H
#define FT_COMMANDSYSTEM_H
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include "Encoding.h"
#include "TextDict.h"
#include "Encoding.h"
namespace zhukova
{
  using str = std::string;
  struct CommandSystem
  {
    std::map< str, void (*)(std::istream& in, std::ostream& out) > common;
    std::map< str, void (*)(TextDict& srcT, std::istream& in, std::ostream& out) > textCommands;
    std::map< str, void (*)(EncodingDict& srcE, std::istream& in, std::ostream& out) > encodingCommands;
    std::map< str, void (*)(TextDict& srcT, EncodingDict& srcE, std::istream& in, std::ostream& out) > bothCommands;
  };
  CommandSystem makeCommandSystem();
  using inS = std::istream;
  using outS = std::ostream;
  void doCommand(TextDict& texts, EncodingDict& encodings, const CommandSystem& cs, const str& command, inS& in, outS& out);
  str inputCommand(std::istream& in);
}
#endif
