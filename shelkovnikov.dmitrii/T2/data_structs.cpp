#include "data_structs.h"
namespace dimkashelk
{
  std::istream &operator>>(std::istream &in, complex_type &c)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    using sep = DelimiterIO;
    double real = 0.0;
    double imag = 0.0;
    in >> sep{'#'} >> sep{'c'} >> sep{'('} >> real >> imag >> sep{')'};
    c = complex_type(real, imag);
    return in;
  }
  std::istream &operator>>(std::istream &in, rational_number &c)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    using sep = DelimiterIO;
    long long first = 0;
    unsigned long long second = 0;
    in >> sep{'('} >> sep{':'} >> sep{'N'} >> first >> sep{':'} >> sep{'D'} >> second >> sep{':'} >> sep{')'};
    c = rational_number{first, second};
    return in;
  }
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
  std::istream &operator>>(std::istream &in, ComplexIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> dest.ref;
  }
  std::istream &operator>>(std::istream &in, StringIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
  }
  std::istream &operator>>(std::istream &in, LabelIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string data = "";
    in >> data;
    in.putback(data.back());
    data.pop_back();
    if (in && (data != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
  std::istream &operator>>(std::istream &in, RationalNumberIO &&c)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> c.ref;
  }
  std::istream &operator>>(std::istream &in, DataStruct &dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DataStruct input;
    {
      using sep = DelimiterIO;
      using label = LabelIO;
      using str = StringIO;
      using cmx = ComplexIO;
      using rtn = RationalNumberIO;
      in >> sep{'('};
      for (unsigned i = 0; i < 3; i++)
      {
        size_t number = 0;
        in >> sep{':'};
        sentry = std::istream::sentry(in);
        in >> label{"key"};
        sentry = std::istream::sentry(in);
        in >> number;
        sentry = std::istream::sentry(in);
        if (number == 1)
        {
          in >> cmx{input.key1};
        }
        else if (number == 2)
        {
          in >> rtn{input.key2};
        }
        else if (number == 3)
        {
          in >> str{input.key3};
        }
      }
      in >> sep{':'} >> sep{')'};
    }
    sentry = std::istream::sentry(in);
    if (in)
    {
      dest = input;
    }
    return in;
  }
  std::ostream &operator<<(std::ostream &out, const complex_type &c)
  {
    out << '(' << c.real() << ' ' << c.imag() << ')';
    return out;
  }
  std::ostream &operator<<(std::ostream &out, const rational_number &c)
  {
    out << "(:N " << c.first << ":D " << c.second << ":)";
    return out;
  }
  std::ostream &operator<<(std::ostream &out, const DataStruct &src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << "(:key1 #c";
    out << std::fixed << std::setprecision(1) << src.key1;
    out << ":key2 ";
    out << std::fixed << std::setprecision(0) << src.key2;
    out << ":key3 \"" << src.key3 << "\":)";
    return out;
  }
  bool Comparator::operator()(const dimkashelk::DataStruct &lhs, const dimkashelk::DataStruct &rhs) const
  {
    if (abs(lhs.key1) == abs(rhs.key1))
    {
      if (lhs.key2 == rhs.key2)
      {
        return lhs.key3.length() < rhs.key3.length();
      }
      return lhs.key2 < rhs.key2;
    }
    return abs(lhs.key1) < abs(rhs.key1);
  }
  iofmtguard::iofmtguard(std::basic_ios< char > &s) :
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
  {}
  iofmtguard::~iofmtguard()
  {
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
  }
}
