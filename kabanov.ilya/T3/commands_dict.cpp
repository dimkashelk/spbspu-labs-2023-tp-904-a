#include "commands_dict.hpp"

#include <string>

#include "commands.hpp"

kabanov::CommandContainer::CommandContainer():
  simple_commands(simpleCommands()),
  sized_commands(sizedCommands()),
  complex_commands(complexCommands())
{}

std::string kabanov::CommandContainer::InputCommand(std::istream& in)
{
  std::string res;
  in >> res;
  if (!in)
  {
    throw std::runtime_error("Input error");
  }
  if (res == "LESSAREA" || res == "RIGHTSHAPES")
  {
    return res;
  }
  std::string temp;
  in >> temp;
  if (!in)
  {
    throw std::invalid_argument("Invalid command");
  }
  res += ' ' + temp;
  return res;
}

void kabanov::CommandContainer::doCommand(std::string command, const std::vector< kabanov::Polygon >& data,
  std::ostream& out, std::istream& in)
{
  try
  {
    complex_commands.at(command)(data, out, in);
    return;
  }
  catch (const std::out_of_range& e)
  {
  }
  try
  {
    simple_commands.at(command)(data, out);
    return;
  }
  catch (const std::out_of_range& e)
  {
  }
  auto spaceIndex = command.find(' ');
  auto index = std::stoull(command.substr(spaceIndex));
  sized_commands.at(command.substr(0, spaceIndex))(data, out, index);
}

kabanov::simpleCommandsStorage kabanov::CommandContainer::simpleCommands()
{
  simpleCommandsStorage dic;
  dic["AREA EVEN"] = printAreaEven;
  dic["AREA ODD"] = printAreaOdd;
  dic["AREA MEAN"] = printAreaMean;
  dic["MAX AREA"] = printMaxArea;
  dic["MIN AREA"] = printMinArea;
  dic["MAX VERTEXES"] = printMaxVertex;
  dic["MIN VERTEXES"] = printMinVertex;
  dic["COUNT EVEN"] = printCountEven;
  dic["COUNT ODD"] = printCountOdd;
  dic["RIGHTSHAPES"] = printRightShapes;
  return dic;
}

kabanov::sizedCommandsStorage kabanov::CommandContainer::sizedCommands()
{
  sizedCommandsStorage dic;
  dic["AREA"] = printAreaNumOfVertex;
  dic["COUNT"] = printCountNumOfVertex;
  return dic;
}

kabanov::complexCommandsStorage kabanov::CommandContainer::complexCommands()
{
  complexCommandsStorage dic;
  dic["LESSAREA"] = printLessArea;
  return dic;
}
