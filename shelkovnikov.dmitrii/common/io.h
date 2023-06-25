#ifndef SPBSPU_LABS_2023_TP_904_A_IO_H
#define SPBSPU_LABS_2023_TP_904_A_IO_H
#include <complex>
#include <map>
#include "data_struct.h"
namespace dimkashelk
{
  struct DelimiterIO
  {
    char exp;
  };
  struct ComplexIO
  {
    complex_type &ref;
  };
  struct RationalNumberIO
  {
    rational_number &ref;
  };
  struct StringIO
  {
    std::string &ref;
  };
  struct LabelIO
  {
    std::string exp;
  };
  class iofmtguard
  {
  public:
    explicit iofmtguard(std::basic_ios< char > &s);
    ~iofmtguard();
  private:
    std::basic_ios< char > &s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };
  class MapPair
  {
  public:
    MapPair(const std::pair< const std::string, size_t > &data):
      data_(data)
    {}
    friend std::ostream &operator<<(std::ostream &out, const MapPair &pair);
  private:
    std::pair< const std::string, size_t > data_;
  };
  std::istream &operator>>(std::istream &in, complex_type &c);
  std::istream &operator>>(std::istream &in, rational_number &c);
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream &operator>>(std::istream &in, ComplexIO &&c);
  std::istream &operator>>(std::istream &in, RationalNumberIO &&c);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::istream &operator>>(std::istream &in, LabelIO &&dest);
  std::istream &operator>>(std::istream &in, DataStruct &dest);
  std::ostream &operator<<(std::ostream &out, const DataStruct &dest);
}
#endif
