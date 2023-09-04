#ifndef STRUCT_IO_H
#define STRUCT_IO_H
#include <string>

struct delimiter_sep
{
  char sep;
};

struct delimiter_IO
{
  char exp;
};

struct string_IO
{
  std::string& ref;
};

struct DBL_sciIO
{
  double& ref;
};

struct ULL_hexIO
{
  unsigned long long& ref;
};

std::istream& operator>>(std::istream&, delimiter_sep&& dest);
std::istream& operator>>(std::istream&, delimiter_IO&& dest);
std::istream& operator>>(std::istream&, string_IO&& dest);
std::istream& operator>>(std::istream&, DBL_sciIO&& dest);
std::istream& operator>>(std::istream&, ULL_hexIO&& dest);

std::ostream& operator<<(std::ostream& out, const DBL_sciIO& dest);

#endif
