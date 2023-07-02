#ifndef FT_WORD_H
#define FT_WORD_H
#include <string>
#include <ostream>
namespace dimkashelk
{
  class Word
  {
  public:
    explicit Word(const std::string &data);
    bool operator<(const Word &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const Word &word);
  private:
    std::string data_;
  };
}
#endif
