#ifndef T2_DATAIO_H
#define T2_DATAIO_H
#include <string>
#include <complex>
#include <iomanip>
#include <iostream>
#include <iterator>
#include "Geometry.h"
namespace zhukova
{
  struct DelimiterIO
  {
    char value;
  };
  class iofmtguard
  {
   public:
    iofmtguard(std::basic_ios< char > & s);
    ~iofmtguard();
   private:
    std::basic_ios< char > & s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };
  std::istream & operator>>(std::istream & in, DelimiterIO && dest);
  std::istream & operator>>(std::istream & in, Polygon & dest);
  std::ostream & operator<<(std::ostream & out, const Point & src);
  std::ostream & operator<<(std::ostream & out, const std::vector< Point > & src);
  std::ostream & operator<<(std::ostream & out, const Polygon & dest);
}
#endif //T2_DATAIO_H
