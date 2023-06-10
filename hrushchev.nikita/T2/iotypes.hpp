#ifndef IOTYPES_HPP
#define IOTYPES_HPP

#include <string>
#include <complex>

namespace hrushchev
{
  struct DelimiterIO
  {
    char exp;
  };

  struct UnsignedLongLongIO
  {
    unsigned long long& num;
  };

  struct ComplexIO
  {
    double real;
    double imag;
  };

  struct StringIO
  {
    std::string str;
  };

  struct LabelIO
  {
    std::string std;
  }
  
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, UnsignedLongLongIO&& dest);
  std::istream& operator>>(std::istream& in, ComplexIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
}
#endif
