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
    dest.x = 0;
    dest.y = 0;
    int x = 0;
    int y = 0;
    in >> std::noskipws >> DelimiterIO{' '};
    if (!in) {
      throw std::invalid_argument("wrong point");
    }
    in >> DelimiterIO{'('} >> x >> DelimiterIO{';'} >> y >> DelimiterIO{')'};
    if (in)
    {
      dest.x = x;
      dest.y = y;
    }
    else
    {
      throw std::invalid_argument("wrong point");
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
    in >> std::noskipws;
    in >> amount;
    if (amount >= 3)
    {
      using in_iter = std::istream_iterator< zhukova::Point >;
      Polygon input;
      try {
      std::copy_n(in_iter(in), amount, std::back_inserter(input.points));
    }
      catch (const std::invalid_argument & e)
      {
        in.clear();
      }
      if (in)
      {
        if (input.points.size() >= 3) {
          std::swap(input, dest);
          return in;
        }
        throw std::logic_error{"<INVALID COMMAND>"};
      }
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
}
