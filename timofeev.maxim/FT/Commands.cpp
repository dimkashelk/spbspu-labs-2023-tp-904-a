#include "Commands.h"
#include <map>
#include "cmdRealisation.h"
namespace timofeev
{
  void command(input& command)
  {
    command["DictList"] = printDictList;
    command["Create"] = Createdict;
    command["Help"] = printHelp;
    command["AddWord"] = AddWord;
    command["Exist"] = Exist;
    command["DeleteT"] = DeleteT;
    command["Delete"] = Delete;
    command["Print"] = Print;
    command["Translate"] = Translate;
    command["Common"] = Common;
  }
}
