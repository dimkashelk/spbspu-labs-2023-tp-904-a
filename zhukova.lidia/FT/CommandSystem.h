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
  struct CommandSystem
  {
    std::map< std::string, void (*)(std::istream & in, std::ostream & out) > common;
    std::map< std::string, void (*)(TextDict & srcTexts, 
                                    std::istream & in, std::ostream & out) > textCommands;
    std::map< std::string, void (*)(EncodingDict & srcEncoding, 
                                    std::istream & in, std::ostream & out) > encodingCommands;
    std::map< std::string, void (*)(TextDict & srcTexts, EncodingDict & srcEncoding, 
                                    std::istream & in, std::ostream & out) > bothCommands;
  };
  CommandSystem makeCommandSystem();
  void commandWasSuccessful();
  void doCommand(TextDict & texts, EncodingDict & encodings,
                 const CommandSystem & cs, const std::string & command,
                 std::istream & in, std::ostream & out);
  std::string inputCommand(std::istream & in);
}
#endif
