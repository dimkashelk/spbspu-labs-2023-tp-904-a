#ifndef T3_POLYGONIO_H
#define T3_POLYGONIO_H
#include <string>
#include <complex>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <algorithm>
#include <DelimiterIO.h>
#include "Geometry.h"
namespace zhukova
{
  std::istream & operator>>(std::istream & in, Point & dest);
  std::istream & operator>>(std::istream & in, Polygon & dest);
}
#endif
