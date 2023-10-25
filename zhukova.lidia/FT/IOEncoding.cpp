#include "IOEncoding.h"
namespace zhukova
{
  bool checkBit(char bit)
  {
    if ((bit != '1') && (bit != '0'))
    {
      throw std::invalid_argument("<wrong file content>");
    }
    return bit == '1';
  }
  std::istream& operator>>(std::istream& in, NameIO& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> std::noskipws >> DelimiterIO{ ' ' } >> dest.name;
    return in;
  }
  std::istream & operator>>(std::istream & in, EncodingNode & dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string code;
    in >> std::noskipws >> dest.symbol >> DelimiterIO{ ' ' };
    in >> dest.probability >> DelimiterIO{ ' ' } >> code >> DelimiterIO{ '\n' };
    using namespace std::placeholders;
    dest.code.clear();
    std::transform(code.begin(), code.end(), std::back_inserter(dest.code), checkBit);
    return in;
  }
  std::istream & operator>>(std::istream & in, Encoding & dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> std::noskipws >> dest.sumAmount >> DelimiterIO{ '\n' };
    using in_iter = std::istream_iterator< EncodingNode >;
    std::copy(in_iter(in), in_iter(), std::back_inserter(dest.list));
    in >> std::skipws;
    return in;
  }
  std::ostream & operator<<(std::ostream & out, const EncodingNode & src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << src.symbol << " " << src.probability << " ";
    std::copy(src.code.begin(), src.code.end(), std::ostream_iterator<bool>(out, ""));
    return out;
  }
  std::ostream& operator<<(std::ostream& out, const std::vector<EncodingNode>& src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    std::copy(src.begin(), src.end(), std::ostream_iterator<EncodingNode>(out, "\n"));
    return out;
  }
  std::ostream & operator<<(std::ostream & out, const Encoding & src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << src.sumAmount << '\n' << src.list;
    return out;
  }
}
