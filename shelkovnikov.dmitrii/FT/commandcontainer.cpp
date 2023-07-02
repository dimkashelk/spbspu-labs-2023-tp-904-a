#include "commandcontainer.h"
#include <iostream>
#include "commands.h"
using con = dimkashelk::CommandContainer;
con::CommandContainer(std::istream &in, std::ostream &out):
  in_(in),
  out_(out),
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
  iofmtguard in_guard(in_);
  iofmtguard out_guard(out_);
  try
  {
    auto comm = dictWithName_.at(command);
    auto f = inputString();
    comm(data_, f);
  }
  catch (const std::out_of_range &e)
  {}
  try
  {
    auto comm = dictWith2Name_.at(command);
    auto p = input2String();
    comm(data_, p.first, p.second);
  }
  catch (const std::out_of_range &e)
  {}
  try
  {
    auto comm = dictWith3Name_.at(command);
    auto p = input3String();
    comm(data_, std::get< 0 >(p), std::get< 1 >(p), std::get< 2 >(p));
  }
  catch (const std::out_of_range &e)
  {}
  try
  {
    auto comm = dictWithSizeT_.at(command);
    comm(data_, inputString(), inputSizeT(), out_);
  }
  catch (const std::out_of_range &e)
  {}
  try
  {
    auto comm = dictWith2NameOstream_.at(command);
    auto p = input2String();
    comm(data_, p.first, p.second, out_);
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
