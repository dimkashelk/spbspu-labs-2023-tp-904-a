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
      cs.dict.at(command)(src, out);
      return;
    } catch (std::out_of_range & e)
    {
    }
    try
    {
      if ((command == "LESSAREA") || (command == "ECHO"))
      {
        std::string strPol;
        std::getline(in, strPol, '\n');
        std::istringstream iss(strPol+'\0');
        Polygon pol;
        iss >> pol;
        if ((pol.points.size() < 3) || ((!iss.eof()) && (iss.peek() != '\0')))
        {
          throw std::logic_error("<INVALID COMMAND>");
        }
        if (in)
        {
          cs.dictPolygon.at(command)(src, pol, out);
        }
        return;
      }
    } catch (std::out_of_range & e)
    {
    }
    try
    {
      std::istringstream iss(command);
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
    std::string firstPart;
    in >> firstPart;
    if ((firstPart == "LESSAREA") || (firstPart == "ECHO"))
    {
      return firstPart;
    }
    std::string secondPart;
    in >> secondPart;
    return firstPart + " " + secondPart;
  }
}
