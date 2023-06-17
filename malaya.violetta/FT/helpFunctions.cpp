#include "helpFunctions.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>
namespace malaya
{
  std::ostream & printNotFound(std::ostream & out)
  {
    out << "<NOT FOUND>";
    return out;
  }
  std::ostream & printInvalid(std::ostream & out)
  {
    out << "<INVALID COMMAND>";
    return out;
  }
  std::ostream & printYesNo(std::ostream & out, bool number)
  {
    return number ? out << "YES" : out << "NO";
  }
  dictionary & findDict(dictOfDicts & dicts, const std::string & name)
  {
    return dicts.at(name);
  }
  std::istream & operator>>(std::istream & in,
    std::pair< std::string, dictionary > && pair)
  {
    std::istream::sentry istreamChecker(in);
    if (!istreamChecker)
    {
      return in;
    }
    using inIt = std::istream_iterator< std::string >;
    in >> pair.first;
    size_t size;
    in >> size;
    //std::copy_n(inIt(in), size, std::inserter(pair.second, pair.second.end())); // сделать структуру word
  }

}