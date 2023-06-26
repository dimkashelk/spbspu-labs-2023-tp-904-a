#ifndef FT_COMMANDCONTAINER_H
#define FT_COMMANDCONTAINER_H
#include "commands.h"
namespace dimkashelk
{
  using func_with_name = void(*)(all_data &, c_s);
  using func_with_2_name = void(*)(all_data &, c_s, c_s);
  using func_with_3_name = void(*)(all_data &, c_s, c_s, c_s);
  using func_with_size_t = void(*)(all_data &, c_s, size_t, std::ostream &);
  class CommandContainer
  {
  public:
    CommandContainer();
  private:
  };
}
#endif