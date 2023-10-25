#ifndef SPBSPU_LABS_2023_TP_904_A_DATA_STRUCTS_H
#define SPBSPU_LABS_2023_TP_904_A_DATA_STRUCTS_H
#include <complex>
#include <string>
namespace dimkashelk
{
  using complex_type = std::complex< double >;
  using rational_number = std::pair< long long, unsigned long long >;
  struct DataStruct
  {
    complex_type key1;
    rational_number key2;
    std::string key3;
  };
  struct Comparator
  {
    bool operator()(const DataStruct &lhs, const DataStruct &rhs) const;
  };
}
#endif
