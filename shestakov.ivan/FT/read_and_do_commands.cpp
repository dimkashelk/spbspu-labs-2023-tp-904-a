#include "read_and_do_commands.h"
#include <functional>
#include "auxiliary_commands.h"
#include "commands_for_dictionaries.h"
#include "commands_for_dictionary.h"

namespace shestakov
{
  using dicts_cmds = std::function< void(my_map &, std::istream &, std::ostream &) >;
  using const_dicts_cmds = std::function< void(const my_map &, std::istream &, std::ostream &) >;
  using dict_cmds = std::function< void(Dictionary &, std::istream &, std::ostream &) >;
  using const_dict_cmds = std::function< void(const Dictionary &, std::istream &, std::ostream &) >;
  std::map< std::string, dicts_cmds > dicts_cmds_
    {
      {"add_dictionary", addDictionary},
      {"delete_dictionary", deleteDictionary},
      {"intersections_dictionary", createIntersectionDict},
      {"read_file", readFile}
    };
  std::map< std::string, const_dicts_cmds > const_dicts_cmds_
    {
      {"search_dictionary", searchDictionary},
      {"count_intersections", countIntersection}
    };
  std::map< std::string, dict_cmds > dict_cmds_
    {
      {"add_word", addWord},
      {"delete_word", deleteWord}
    };
  std::map< std::string, const_dict_cmds > const_dict_cmds_
    {
      {"search_word", searchWord},
      {"count_words", countWords},
      {"count_words_frequency", countWordsWithFreq},
      {"three_most_common", printThreeMostCommonWords},
      {"save_dictionary", saveDictionary}
    };
  void doDictsCmds(my_map &dictionaries, const std::string &cmd, std::istream &in, std::ostream &out)
  {
    auto toexecute = dicts_cmds_.at(cmd);
    toexecute(dictionaries, in, out);
  }
  void doConstDictsCmds(const my_map &dictionaries, const std::string &cmd, std::istream &in, std::ostream &out)
  {
    auto toexecute = const_dicts_cmds_.at(cmd);
    toexecute(dictionaries, in, out);
  }
  void doDictCmds(my_map &dictionaries, const std::string &cmd, std::istream &in, std::ostream &out)
  {
    std::string dict = "";
    if (dict_cmds_.find(cmd) != dict_cmds_.end())
    {
      in >> dict;
      if (!searchDict(dictionaries, dict))
      {
        out << "Dictionary \"" << dict << "\" does not exist.\n";
        skipUntilNewLine(in);
        return;
      }
    }
    auto toexecute = dict_cmds_.at(cmd);
    toexecute(dictionaries[dict], in, out);
  }
  void doConstDictCmds(const my_map &dictionaries, const std::string &cmd, std::istream &in, std::ostream &out)
  {
    std::string dict = "";
    if (const_dict_cmds_.find(cmd) != const_dict_cmds_.end())
    {
      in >> dict;
      if (!searchDict(dictionaries, dict))
      {
        out << "Dictionary \"" << dict << "\" does not exist.\n";
        skipUntilNewLine(in);
        return;
      }
    }
    auto toexecute = const_dict_cmds_.at(cmd);
    my_map::const_iterator const_dict = dictionaries.find(dict);
    toexecute(const_dict->second, in, out);
  }
  void doCommand(my_map &dictionaries, const std::string& cmd, std::istream &in, std::ostream &out)
  {
    try
    {
      doDictsCmds(dictionaries, cmd, in, out);
      return;
    }
    catch (const std::out_of_range &e)
    {}
    try
    {
      doConstDictsCmds(dictionaries, cmd, in, out);
      return;
    }
    catch (const std::out_of_range& e)
    {}
    try
    {
      doDictCmds(dictionaries, cmd, in, out);
      return;
    }
    catch (const std::out_of_range& e)
    {}
    try
    {
      doConstDictCmds(dictionaries, cmd, in, out);
      return;
    }
    catch (const std::out_of_range& e)
    {}
    throw std::logic_error("Invalid command");
  }
}