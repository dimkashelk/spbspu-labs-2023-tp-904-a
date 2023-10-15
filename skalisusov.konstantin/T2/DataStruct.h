#ifndef SPBSPU_LABS_2023_TP_904_A_DATASTRUCT_H
#define SPBSPU_LABS_2023_TP_904_A_DATASTRUCT_H
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <iofmtguard.h>
#include <StructTypes.h>
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
#endif //SPBSPU_LABS_2023_TP_904_A_DATASTRUCT_H
