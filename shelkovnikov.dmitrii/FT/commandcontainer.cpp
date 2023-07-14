#include "commandcontainer.h"
#include <iostream>
#include "commands.h"
using con = dimkashelk::CommandContainer;
con::CommandContainer(std::istream &in, std::ostream &out):
  in_(in),
  out_(out),
  data_(),
  dictWithIstream_(initializeIstream()),
  dictWithOstream_(initializeOstream()),
  dictWithIOstream_(initializeIOstream())
{}
std::map< std::string, func_with_istream > con::initializeIstream()
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
std::map< std::string, func_with_iostream > con::initializeIOstream()
{
  std::map< std::string, func_with_iostream > res;
  res["printWord"] = printWord;
  res["print"] = print;
  res["top"] = getTop;
  return res;
}
std::map< std::string, func_with_ostream > con::initializeOstream()
{
  std::map< std::string, func_with_ostream > res;
  res["help"] = help;
  return res;
}
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
std::string con::inputString()
{
  std::istream::sentry sentry(in_);
  std::string res;
  if (sentry)
  {
    in_ >> res;
    return res;
  }
  else
  {
    throw std::logic_error("Cannot input");
  }
}
std::pair< std::string, std::string > con::input2String()
{
  return {inputString(), inputString()};
}
std::tuple< std::string, std::string, std::string > con::input3String()
{
  return std::tuple< std::string, std::string, std::string >(inputString(), inputString(), inputString());
}
size_t dimkashelk::CommandContainer::inputSizeT()
{
  std::istream::sentry sentry(in_);
  size_t res;
  if (sentry)
  {
    in_ >> res;
    return res;
  }
  else
  {
    throw std::logic_error("Cannot input");
  }
}
