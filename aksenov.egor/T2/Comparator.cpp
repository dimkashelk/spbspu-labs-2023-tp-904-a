#include "Comparator.h"
bool aksenov::comparator(const aksenov::DataStruct &lhs, const aksenov::DataStruct &rhs)
{
  if (lhs.key1 == rhs.key1)
  {
    if (lhs.key2 == rhs.key2)
    {
      return lhs.key3.size() < rhs.key3.size();
    }
    return (abs(lhs.key2) < abs(rhs.key2));
  }
  else
  {
    return lhs.key1 < rhs.key1;
  }
}
