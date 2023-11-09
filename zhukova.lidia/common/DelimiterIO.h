#ifndef DELIMITERIO_H
#define DELIMITERIO_H
#include <iostream>
#include "IOfmtguard.h"
namespace zhukova
{
  struct DelimiterIO
  {
    char value;
  };
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
}
#endif
