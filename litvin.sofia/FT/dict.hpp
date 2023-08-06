#ifndef FT_DICT_HPP
#define FT_DICT_HPP
#include <vector>
#include <string>
#include <map>
namespace litvin
{
  using translations = std::vector< std::string >;
  struct dict_t
  {
    std::map< std::string, translations > dict;
  };
  struct list_of_dicts_t
  {
    std::map< std::string, dict_t > dict_list;
  };
}
#endif
