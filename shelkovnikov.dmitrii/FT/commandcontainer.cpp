#include "commandcontainer.h"
#include <iostream>
#include "commands.h"
std::map< std::string, func_with_istream > initializeIstream()
{
  std::map< std::string, func_with_istream > res;
  res["load"] = load;
  res["analyze"] = analyze;
  res["export"] = exportToFile;
  res["exportWithText"] = exportWithText;
  res["deleteWord"] = deleteWord;
  res["delete"] = deleteDict;
  res["remove"] = remove;
  res["intersect"] = getIntersect;
  res["complement"] = getComplement;
  res["union"] = getUnion;
  return res;
}
std::map< std::string, func_with_iostream > initializeIOstream()
{
  std::map< std::string, func_with_iostream > res;
  res["printWord"] = printWord;
  res["print"] = print;
  res["top"] = getTop;
  return res;
}
std::map< std::string, func_with_ostream > initializeOstream()
{
  std::map< std::string, func_with_ostream > res;
  res["help"] = help;
  return res;
}
using con = dimkashelk::CommandContainer;
con::CommandContainer(std::istream &in, std::ostream &out):
  in_(in),
  out_(out),
  data_(),
  dictWithIstream_(initializeIstream()),
  dictWithOstream_(initializeOstream()),
  dictWithIOstream_(initializeIOstream())
{}
void con::doCommand(const std::string &command)
{
  try
  {
    auto comm = dictWithIstream_.at(command);
    comm(data_, in_);
  }
  catch (const std::out_of_range &e)
  {}
  try
  {
    auto comm = dictWithIOstream_.at(command);
    comm(data_, in_, out_);
  }
  catch (const std::out_of_range &e)
  {}
  try
  {
    auto comm = dictWithOstream_.at(command);
    comm(out_);
  }
  catch (const std::out_of_range &e)
  {}
}
