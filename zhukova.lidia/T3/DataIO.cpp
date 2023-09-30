#include "DataIO.h"
namespace zhukova
{
  std::istream & operator>>(std::istream & in, DelimiterIO && dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '\0';
    in >> c;
    if (in && (c != dest.value))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
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
  std::ostream & operator<<(std::ostream & out, const Point & src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << '(' << src.x << ';' << src.y << ')';
    return out;
  }
  std::ostream & operator<<(std::ostream & out, const std::vector< Point > & src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    std::copy(src.begin(), src.end(), std::ostream_iterator< Point >(std::cout, " "));
    return out;
  }
  std::ostream & operator<<(std::ostream & out, const Polygon & src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << src.points.size() << ' ' << src.points;
    return out;
  }
  iofmtguard::iofmtguard(std::basic_ios< char > & s):
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
  {
  }
  iofmtguard::~iofmtguard()
  {
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
  }
}
