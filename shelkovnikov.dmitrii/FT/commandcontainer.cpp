#include "commandcontainer.h"
#include "commands.h"
using con = dimkashelk::CommandContainer;
con::CommandContainer()
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

