#ifndef FT_WORD_H
#define FT_WORD_H
#include <string>
namespace dimkashelk
{
  class Word
  {
  public:
    explicit Word(const std::string &data);
  private:
    std::string data_;
  };
}
#endif
