#ifndef FT_IOENCODING_H
#define FT_IOENCODING_H
#include <iostream>
#include <iterator>
#include <DelimiterIO.h>
#include <IOfmtguard.h>
#include "Encoding.h"
namespace zhukova{
  struct NameIO {
    std::string name = "";
  }
  bool checkBit(char bit);
  std::istream& operator>>(std::istream& in, NameIO& dest);
  std::istream& operator>>(std::istream & in, EncodingNode & dest);
  std::istream& operator>>(std::istream & in, Encoding & dest);
  std::ostream& operator<<(std::ostream & out, const EncodingNode & src);
  std::ostream& operator<<(std::ostream& out, const std::vector<EncodingNode>& src);
  std::ostream& operator<<(std::ostream & out, const Encoding & src);
}
#endif
