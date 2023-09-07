#ifndef KONCHEV_MAKSIM_DATASTRUCT_H
#define KONCHEV_MAKSIM_DATASTRUCT_H
#include <string>
#include <fstream>
struct DataStruct
{
  long long key1;
  unsigned long long key2;
  std::string key3;
};
std::ifstream &operator>>(std::ifstream &in, DataStruct &&data);
std::ofstream &operator<<(std::ofstream &out, const DataStruct &data);
#endif
