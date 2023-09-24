#ifndef OUTMESSAGES_HPP
#define OUTMESSAGES_HPP
#include <map>
#include "geomfigures.hpp"
namespace kotova
{
  using cmd_out = void (*)(const std::vector< Polygon > &, std::ostream &);
  using cmd_num = void (*)(size_t, const std::vector<Polygon> &, std::ostream &);
  using cmd_fr_same = void (*)(const std::vector< Polygon > &, std::istream &, std::ostream &);
  class CommandDictionary
  {
    public:
      CommandDictionary();
      std::string readCommand(std::istream &in);
      void doCommand(std::string &cmd, std::vector< Polygon > &data,
          std::istream &in, std::ostream &out);
    private:
      std::map<std::string, cmd_out> dict_out;
      std::map<std::string, cmd_num> dict_num;
      std::map<std::string, cmd_fr_same> dict_fr;
      std::map<std::string, cmd_fr_same> dict_same;
      void doCommandOut(std::string &cmd, const std::vector<Polygon> &polygons, std::ostream &out) const;
      void doCommandNum(std::string &cmd, const std::vector<Polygon> &polygons, std::ostream &out, std::size_t n) const;
      void doCommandFr(std::string &cmd, std::vector<Polygon> &polygons, std::ostream &out, std::istream &in) const;
      void doCommandSame(std::string &cmd, std::vector<Polygon> &polygons, std::ostream &out, std::istream &in) const;
  };
}

#endif
