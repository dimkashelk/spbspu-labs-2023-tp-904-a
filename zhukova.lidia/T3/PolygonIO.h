#ifndef T2_DATAIO_H
#define T2_DATAIO_H
#include <string>
#include <complex>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <algorithm>
#include <DataIO.h>
#include "Geometry.h"
namespace zhukova
{
  std::istream & operator>>(std::istream & in, Polygon & dest);
  std::ostream & operator<<(std::ostream & out, const Point & src);
  std::ostream & operator<<(std::ostream & out, const std::vector< Point > & src);
  std::ostream & operator<<(std::ostream & out, const Polygon & dest);
}
#endif //T2_DATAIO_H
