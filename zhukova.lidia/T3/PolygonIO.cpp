#include "PolygonIO.h"
namespace zhukova
{
  std::istream & operator>>(std::istream & in, Point & dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    int x = 0;
    int y = 0;
    in >> DelimiterIO{'('} >> x >> DelimiterIO{';'} >> y >> DelimiterIO{')'};
    if (in)
    {
      dest.x = x;
      dest.y = y;
    }
    return in;
  }
  std::istream & operator>>(std::istream & in, Polygon & dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    dest.points.clear();
    size_t amount = 0;
    in >> amount;
    if (in && amount >= 3)
    {
      using in_iter = std::istream_iterator< zhukova::Point >;
      Polygon input;
      std::copy_n(in_iter(in), amount, std::back_inserter(input.points));
      if (in)
      {
        std::swap(input, dest);
      }
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
}
