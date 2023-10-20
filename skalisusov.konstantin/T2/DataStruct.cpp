#include "DataStruct.hpp"
#include <StructTypes.hpp>
#include <iomanip>
namespace skalisusov
{
  std::istream &operator>>(std::istream &in, DataStruct &dest)
  {
    std::istream::sentry CheckSentry(in);
    if(!CheckSentry)
    {
      return in;
    }
    DataStruct input;
    {
      using sep = DelimiterIO;
      using dubsci = DoubleSciencificFormatI;
      using dublit = DoubleLiteralFormatIO;
      using str = StringIO;
      std::string keyNum = "";
      in >> sep{'('};
      in >> sep{':'};
      for(size_t i = 0; i < 3; i++)
      {
        in >> keyNum;
        if(keyNum == "key1")
        {
          in >> dublit {input.key1} >> sep{':'};
        }
        else if(keyNum == "key2" )
        {
          in >> dubsci{input.key2} >> sep{':'};
        }
        else if(keyNum == "key3" )
        {
          in >> str{input.key3} >> sep{':'};
        }
      }
      in >> sep{')'};
    }
    if(in)
    {
      dest = input;
    }
    return in;
  }
  std::ostream &operator<<(std::ostream &out, const DataStruct &dest)
  {
    std::ostream::sentry CheckSentry(out);
    if(!CheckSentry)
    {
      return out;
    }
    iofmtguard iofmtguard(out);
    out << "(";
    out << ":key1 " << std::fixed << std::setprecision(1) << dest.key1 << 'd';
    out << ":key2 " << DoubleSciencificFormatO{dest.key2};
    out << ":key3 " << '"' << dest.key3 << '"';
    out << ":)";
    return out;
  }
  bool comparate(DataStruct &firDs, DataStruct &secDs)
  {
    if(firDs.key1 != secDs.key1)
    {
      return firDs.key1 < secDs.key1;
    }
    if(firDs.key1 == secDs.key1 && firDs.key2 != secDs.key2)
    {
      return firDs.key2 < secDs.key2;
    }
    else
    {
      return  firDs.key3.length() < secDs.key3.length();
    }
  }
}
