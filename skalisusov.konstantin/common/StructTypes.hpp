#ifndef STRUCTTYPES_HPP
#define STRUCTTYPES_HPP
#include <iostream>
#include <string>
#include <iofmtguard.hpp>
namespace skalisusov
{
  struct LabelIO
  {
    std::string label;
  };
  struct DelimiterIO
  {
    char exp;
  };
  struct StringIO
  {
    std::string &str;
  };
  struct DoubleLiteralFormatIO
  {
    double &dublit;
  };
  struct DoubleSciencificFormatI
  {
    double &dubscienI;
  };
  struct DoubleSciencificFormatO
  {
    const double dubscienO;
  };
  std::istream &operator>>(std::istream &in, LabelIO &&dest);
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream &operator>>(std::istream &in, DoubleLiteralFormatIO &&dest);
  std::istream &operator>>(std::istream &in, DoubleSciencificFormatI &&dest);
  std::ostream &operator<<(std::ostream &out, const DoubleSciencificFormatO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
}
#endif
