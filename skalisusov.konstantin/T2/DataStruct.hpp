#ifndef SPBSPU_LABS_2023_TP_904_A_DATASTRUCT_HPP
#define SPBSPU_LABS_2023_TP_904_A_DATASTRUCT_HPP
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <iofmtguard.hpp>
#include <StructTypes.hpp>
namespace skalisusov
{
  struct DataStruct
  {
    double key1;
    double key2;
    std::string key3;
  };
  std::istream &operator>>(std::istream &in, DataStruct &dest);
  std::ostream &operator<<(std::ostream &out, DataStruct &src);
  bool comparate(DataStruct &firDs, DataStruct &secDs);

}
#endif
