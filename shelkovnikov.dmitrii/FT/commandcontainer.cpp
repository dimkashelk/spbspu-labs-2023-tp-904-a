#include "commandcontainer.h"
#include <iostream>
#include "commands.h"
using con = dimkashelk::CommandContainer;
con::CommandContainer(std::istream &in, std::ostream &out):
  in_(in),
  in_guard_(in_),
  out_(out),
  out_guard_(out_),
  data_(),
  dictWithName_(initializeName()),
  dictWith2Name_(initialize2Name()),
  dictWith3Name_(initialize3Name()),
  dictWithSizeT_(initializeSizeT()),
  dictWith2NameOstream_(initialize2NameOstream()),
  dictWith1NameOstream_(initialize1NameOstream()),
  dictWithOstream_(initializeOstream())
{}
std::map< std::string, dimkashelk::func_with_name > con::initializeName()
{
  std::map< std::string, func_with_name > res;
  res["load"] = load;
  res["analyze"] = analyze;
  res["delete"] = deleteDict;
  res["remove"] = remove;
  return res;
}
std::map< std::string, dimkashelk::func_with_2_name > con::initialize2Name()
{
  std::map< std::string, func_with_2_name > res;
  res["export"] = exportToFile;
  res["exportWithText"] = exportWithText;
  res["deleteWord"] = deleteWord;
  return res;
}
std::map< std::string, dimkashelk::func_with_3_name > con::initialize3Name()
{
  std::map< std::string, func_with_3_name > res;
  res["complement"] = getComplement;
  res["intersect"] = getIntersect;
  res["union"] = getUnion;
  return res;
}
std::map< std::string, dimkashelk::func_with_size_t > con::initializeSizeT()
{
  std::map< std::string, func_with_size_t > res;
  res["top"] = getTop;
  return res;
}
std::map< std::string, dimkashelk::func_with_2_name_ostream > con::initialize2NameOstream()
{
  std::map< std::string, func_with_2_name_ostream > res;
  res["printWord"] = printWord;
  return res;
}
std::map< std::string, dimkashelk::func_with_1_name_ostream > con::initialize1NameOstream()
{
  std::map< std::string, func_with_1_name_ostream > res;
  res["print"] = print;
  return res;
}
std::map< std::string, dimkashelk::func_with_ostream > con::initializeOstream()
{
  std::map< std::string, func_with_ostream > res;
  res["help"] = help;
  return res;
}
void con::doCommand(const std::string &command)
{
  try
  {
    auto comm = dictWithName_.at(command);
    auto f = inputString();
    comm(data_, f);
  }
  catch (const std::out_of_range &e)
  {}
}
std::string dimkashelk::CommandContainer::inputString()
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
