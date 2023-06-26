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
