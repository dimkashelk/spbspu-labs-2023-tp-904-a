#ifndef FT_AUXILIARY_FNS_HPP
#define FT_AUXILIARY_FNS_HPP
#include "commands.hpp"
#include "dict.hpp"
namespace litvin
{
  using command_descriptors = std::map< std::string, std::string >;
  command_descriptors createCommandDescriptorsDict();
  void man(const command_descriptors & cmd_desc, std::ostream & out, std::istream & in);
  void help(const command_descriptors & cmd_desc, std::ostream & out, std::istream & in);
  class command_dict_t
  {
   public:
    command_dict_t();
    void executeCommand(const std::string & command, dicts_list_t & list, std::ostream & out, std::istream & in) const;
    void executeCommand(const std::string & command, dicts_list_t & list, const std::string & dict,
                        std::ostream & out) const;
    void executeCommand(const std::string & command, const command_descriptors & cmd_desc, std::ostream & out,
                        std::istream & in) const;
   private:
    using signature_type_1 = void (*)(dicts_list_t &, std::ostream &, std::istream &);
    using signature_type_2 = void (*)(const command_descriptors &, std::ostream &, std::istream &);
    using signature_type_3 = void (*)(dicts_list_t &, const std::string &, std::ostream &);
    std::map< std::string, signature_type_1 > dict1;
    std::map< std::string, signature_type_2 > dict2;
    std::map< std::string, signature_type_3 > dict3;
  };
  std::string inputCommand(std::istream & in);
  void runCommand(const command_dict_t & cmd_d, dicts_list_t & list, const command_descriptors & desc_d,
                  const std::string & cmd, std::ostream & out, std::istream & in);
}
#endif
