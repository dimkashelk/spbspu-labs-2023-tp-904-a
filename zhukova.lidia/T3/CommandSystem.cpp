#include "CommandSystem.h"
namespace zhukova
{
  CommandSystem makeCommandSystem()
  {
    CommandSystem commands;
    commands.dict.insert({"AREA EVEN", getSumAreaEven});
    commands.dict.insert({"AREA ODD", getSumAreaOdd});
    commands.dict.insert({"AREA MEAN", getAreaMean});
    commands.dict.insert({"COUNT EVEN", countEvenVertexes});
    commands.dict.insert({"COUNT ODD", countOddVertexes});
    commands.dict.insert({"MAX VERTEXES", getMaxVertexes});
    commands.dict.insert({"MIN VERTEXES", getMinVertexes});
    commands.dict.insert({"MAX AREA", getMaxArea});
    commands.dict.insert({"MIN AREA", getMinArea});
    commands.dictNumber.insert({"AREA", getSumAreaVertexes});
    commands.dictNumber.insert({"COUNT", countExactVertexes});
    commands.dictPolygon.insert({"LESSAREA", getAmountWithLessArea});
    commands.dictPolygon.insert({"ECHO", echo});
    return commands;
  }
  void doCommand(std::vector< Polygon > & src, const CommandSystem & cs, const std::string & command,
                 std::istream & in, std::ostream & out)
  {
    try
    {
      if (in)
      {
        cs.dict.at(command)(src, out);
      }
      return;
    }
    catch (const std::out_of_range & e)
    {
    }
    try
    {
      if ((command == "LESSAREA") || (command == "ECHO"))
      {
        Polygon pol;
        in >> pol;
        in >> std::noskipws >> DelimiterIO{'\n'} >> std::skipws;
        if (in)
        {
          cs.dictPolygon.at(command)(src, pol, out);
          return;
        }
        in.setstate(std::ios::failbit);
        throw std::logic_error("<INVALID COMMAND>");
      }
    }
    catch (const std::out_of_range & e)
    {
    }
    try
    {
      size_t endOfWord = command.find(' ');
      std::string word = command.substr(0, endOfWord);
      size_t number = std::stoull(command.substr(endOfWord));
      cs.dictNumber.at(word)(src, number, out);
    }
    catch (const std::out_of_range & e)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
  }
  std::string inputCommand(std::istream & in)
  {
    std::string command;
    in >> command;
    if ((command == "AREA") || (command == "COUNT") || (command == "MAX") || (command == "MIN"))
    {
      std::string parameter;
      in >> parameter;
      if (!in)
      {
        throw std::logic_error("<INVALID COMMAND>");
      }
      command = command + " " + parameter;
    }
    return command;
  }
}
