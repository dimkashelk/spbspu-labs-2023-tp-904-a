#include "CommandSystem.h"
#include "Commands.h"
namespace zhukova
{
  CommandSystem makeCommandSystem()
  {
    CommandSystem commands;
    commands.common.insert({"help", printAllCommands});
    commands.textCommands.insert({"load", loadText});
    commands.bothCommands.insert({"getEncoding", getEncoding});
    commands.encodingCommands.insert({"saveEncoding", saveEncoding});
    commands.encodingCommands.insert({ "loadEncoding", loadEncoding });
    commands.bothCommands.insert({"codedWith", codedWith});
    commands.bothCommands.insert({"code", code});
    commands.bothCommands.insert({"codeWith", codeWith});
    commands.bothCommands.insert({"decode", decode});
    commands.textCommands.insert({"concat", concatenate});
    commands.textCommands.insert({"save", saveText});
    commands.bothCommands.insert({"compare", compare});
    commands.common.insert({"weight", weight});
    return commands;
  }
  void commandWasSuccessful()
  {
    std::cout << "Success\n";
  }
  void doCommand(TextDict & texts, EncodingDict & encodings,
                 const CommandSystem & cs, const std::string & command,
                 std::istream & in, std::ostream & out)
  {
    try
    {
      cs.common.at(command)(in, out);
      return;
    } catch (std::out_of_range & e)
    {
    }
    try
    {
      cs.textCommands.at(command)(texts, in, out);
      return;
    }
    catch (std::out_of_range & e)
    {
    }
    try
    {
      cs.encodingCommands.at(command)(encodings, in, out);
      return;
    } catch (std::out_of_range & e)
    {
    }
    try
    {
      cs.bothCommands.at(command)(texts, encodings, in, out);
      return;
    }
    catch (std::out_of_range & e)
    {
      throw std::invalid_argument("<invalid command>");
    }
  }
  std::string inputCommand(std::istream & in)
  {
    std::string command;
    in >> command;
    if (!in) {
      throw std::invalid_argument("<invalid command>");
    }
    return command;
  }
}
