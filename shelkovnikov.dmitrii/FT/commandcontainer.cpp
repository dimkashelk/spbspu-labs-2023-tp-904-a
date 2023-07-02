#include "commandcontainer.h"
#include "commands.h"
using con = dimkashelk::CommandContainer;
con::CommandContainer():
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
