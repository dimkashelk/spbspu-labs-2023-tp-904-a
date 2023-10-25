#ifndef FORMATGUARDIO_HPP
#define FORMATGUARDIO_HPP

#include <iomanip>

namespace kabanov
{
  class FormatGuardIO
  {
  public:
    explicit FormatGuardIO(std::basic_ios< char >& s);
    ~FormatGuardIO();
  private:
    std::basic_ios< char >& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags flags_;
  };
}
#endif
