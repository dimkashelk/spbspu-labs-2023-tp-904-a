#ifndef FT_MAPPAIR_H
#define FT_MAPPAIR_H
#include <iostream>
#include "word.h"
namespace dimkashelk
{
  class MapPair
  {
  public:
    MapPair(const std::pair< const Word, size_t > &data):
      data_{data.first, data.second}
    {}
    friend std::ostream &operator<<(std::ostream &out, const MapPair &pair);
    friend bool operator<(const MapPair &lnr, const MapPair &rnl);
  private:
    std::pair< Word, size_t > data_;
  };
}
#endif
