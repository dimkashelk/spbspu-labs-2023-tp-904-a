#ifndef FT_DICT_HPP
#define FT_DICT_HPP
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
namespace litvin
{
  using translations = std::vector< std::string >;
  using dict_t = std::map< std::string, translations >;
  struct dicts_list_t
  {
    std::unordered_map< std::string, dict_t > dict_list;
  };
}
#endif
