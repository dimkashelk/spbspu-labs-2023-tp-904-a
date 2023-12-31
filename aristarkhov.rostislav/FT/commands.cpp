#include "commands.h"
#include "dictionaryCommands.h"

namespace aristarkhov
{
  CommandProcessor::CommandProcessor(): commandsList
  {{"help", printHelp},
   {"create", createDictionary},
   {"deleteWord", deleteWord},
   {"deleteDataset", deleteDictionary},
   {"findWord", findWord},
   {"getWordCount", getWordCount},
   {"clear", clearDictionary},
   {"getFrequency", getFrequency},
   {"getMostUseWord", getMostUseWord},
   {"remove", removeText},
   {"readText", readTextIntoDictionary},
   {"readFile", readFile},
   {"complement", complementDictionary},
   {"intersect", intersectDictionary},
   {"union", unionDictionary}}
  {
  }

  void CommandProcessor::processCommand(dictionaryOfNames& dictionaries, const std::string cmd, std::istream& in, std::ostream& out)
  {
    if (commandsList.count(cmd))
    {
      commandsList[cmd](dictionaries, in, out);
    }
    else
    {
      printError(out);
    }
  }
}
