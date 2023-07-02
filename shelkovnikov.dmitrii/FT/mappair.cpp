#include "mappair.h"
std::ostream &dimkashelk::operator<<(std::ostream &out, const dimkashelk::MapPair &pair)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  return out << pair.data_.first << ": " << pair.data_.second;
}
bool dimkashelk::operator<(const dimkashelk::MapPair &lnr, const dimkashelk::MapPair &rnl)
{
  auto &l_sec = lnr.data_.second;
  auto &r_sec = rnl.data_.second;
  auto &l_fir = rnl.data_.first;
  auto &r_fir = rnl.data_.first;
  return l_sec < r_sec || (l_sec == r_sec && l_fir < r_fir);
}
