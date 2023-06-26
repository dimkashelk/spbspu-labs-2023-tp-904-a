#ifndef FT_COMMANDCONTAINER_H
#define FT_COMMANDCONTAINER_H
#include "commands.h"
namespace dimkashelk
{
  using func_with_name = void(*)(all_data &, c_s);
  class CommandContainer
  {
  public:
    CommandContainer();
  private:
  };
}
#endif
