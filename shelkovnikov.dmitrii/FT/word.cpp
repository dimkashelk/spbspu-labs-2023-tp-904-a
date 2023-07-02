#include "word.h"
dimkashelk::Word::Word(const std::string &data):
  data_(data)
{}
bool dimkashelk::Word::operator<(const dimkashelk::Word &rhs) const
{
  return data_ < rhs.data_;
}
