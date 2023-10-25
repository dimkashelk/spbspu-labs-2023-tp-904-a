#include "commands.h"
#include <limits>
#include <stdexcept>
#include <algorithm>
#include "commandsImpl.h"

namespace aksenov
{
  std::string insertCommand(std::istream &in)
  {
    std::string command = "";
    in >> command;
    if (!in)
    {
      throw std::runtime_error("empty stream");
    }
    return command;
  }

  Commands::Commands()
  {
    dict_.insert({"CREATE", createDict});
    dict_.insert({"OUT", outDictionaries});
    dict_.insert({"TRANSLATE", translate});
    dict_.insert({"HELP", help});
    dict_.insert({"INTERSECTION", doIntersect});
    dict_.insert({"UNITE", unite});
  }

  void Commands::doCommand(std::string &command, std::istream &in, dictOfDicts &dict, std::ostream &out)
  {
    auto func = dict_.at(command);
    func(command, in, dict, out);
  }

  void executeCommand(std::ostream &out, std::istream &in, Commands &commands, dictOfDicts &dict, std::string command)
  {
    try
    {
      commands.doCommand(command, in, dict, out);
    }
    catch (const std::out_of_range &e)
    {
      out << "command not found" << "\n";
    }
  }
}
