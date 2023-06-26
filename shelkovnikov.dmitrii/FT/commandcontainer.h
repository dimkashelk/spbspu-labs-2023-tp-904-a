#ifndef FT_COMMANDCONTAINER_H
#define FT_COMMANDCONTAINER_H
#include "commands.h"
namespace dimkashelk
{
  using func_with_name = void(*)(all_data &, c_s);
  using func_with_2_name = void(*)(all_data &, c_s, c_s);
  using func_with_3_name = void(*)(all_data &, c_s, c_s, c_s);
  using func_with_size_t = void(*)(all_data &, c_s, size_t, std::ostream &);
  using func_with_2_name_ostream = void(*)(all_data &, c_s, c_s, std::ostream &);
  using func_with_1_name_ostream = void(*)(all_data &, c_s, std::ostream &);
  using func_with_ostream = void(*)(std::ostream &);
  class CommandContainer
  {
  public:
    CommandContainer();
  private:
    std::map< std::string, func_with_name > initializeName();
    std::map< std::string, func_with_2_name > initialize2Name();
    std::map< std::string, func_with_3_name > initialize3Name();
    std::map< std::string, func_with_size_t > initializeSizeT();
    std::map< std::string, func_with_2_name_ostream > initialize2NameOstream();
    std::map< std::string, func_with_1_name_ostream > initialize1NameOstream();
    std::map< std::string, func_with_ostream > initializeOstream();
  };
}
#endif
