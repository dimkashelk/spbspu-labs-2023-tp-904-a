#ifndef FT_AUXILIARY_FNS_HPP
#define FT_AUXILIARY_FNS_HPP
#include "commands.hpp"
#include "dict.hpp"
namespace litvin
{
  struct command_dict_t
  {
    command_dict_t();
    using signature_type_1 = void (*)(dicts_list_t & list, const std::string & mysterious_str, std::ostream & out);
    using signature_type_2 = void (*)(dicts_list_t & list, const std::string & dict,
                                      const std::string & mysterious_str1,
                                      const std::string & mysterious_str2, std::ostream & out);
    using signature_type_3 = void (*)(dicts_list_t & list, const std::string & dict, const std::string & mysterious_str,
                                      std::ostream & out);
    using signature_type_4 = void (*)(dicts_list_t & list, const std::string & dict, const std::string & word,
                                      size_t num_of_translation, const std::string & new_translation,
                                      std::ostream & out);
    using signature_type_5 = void (*)(dicts_list_t & list, const std::string & dict, const std::string & word,
                                      size_t num_of_translation, std::ostream & out);
    std::map< std::string, signature_type_1 > dict1;
    std::map< std::string, signature_type_2 > dict2;
    std::map< std::string, signature_type_3 > dict3;
    std::map< std::string, signature_type_4 > dict4;
    std::map< std::string, signature_type_5 > dict5;
  };
  using command_descriptors = std::map<std::string, std::string>;
  command_descriptors createCommandDescriptorsDict();
  void man(const command_descriptors & cmd_desc, const std::string & command, std::ostream & out);
  void help(const command_descriptors & cmd_desc, std::ostream & out);
}
#endif
