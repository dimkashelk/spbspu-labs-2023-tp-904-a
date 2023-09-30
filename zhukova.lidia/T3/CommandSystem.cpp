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
                 std::ostream & out)
  {
    try
    {
      cs.dict.at(command)(src, out);
      return;
    } catch (std::out_of_range & e)
    {
    }
    try
    {
      std::istringstream iss(command + '\0');
      std::string word;
      iss >> word;
      if ((word == "LESSAREA") || (word == "ECHO"))
      {
        Polygon pol;
        iss >> pol;
        if ((pol.points.size() < 3) || ((!iss.eof()) && (iss.peek() != '\0')))
        {
          throw std::logic_error("<INVALID COMMAND>");
        }
        if (iss)
        {
          cs.dictPolygon.at(word)(src, pol, out);
        }
        return;
      }
    } catch (std::out_of_range & e)
    {
    }
    try
    {
      std::istringstream iss(command + '\0');
      std::string word;
      iss >> word;
      size_t number;
      iss >> number;
      cs.dictNumber.at(word)(src, number, out);
    } catch (std::out_of_range & e)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
  }
  std::string inputCommand(std::istream & in)
  {
    std::string command;
    std::getline(in, command, '\n');
    return command;
  }
}
