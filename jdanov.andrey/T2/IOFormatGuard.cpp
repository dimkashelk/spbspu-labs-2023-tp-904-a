#include "IOFormatGuard.h"

namespace zhdanov
{
  IOFormatGuard::IOFormatGuard(std::basic_ios< char >& stream) :
  	referenceToStream_(stream),
  	fill_(stream.fill()),
  	precision_(stream.precision()),
  	formatFlags_(stream.flags())
  {
  }
  IOFormatGuard::~IOFormatGuard()
  {
  	referenceToStream_.fill(fill_);
  	referenceToStream_.precision(precision_);
  	referenceToStream_.flags(formatFlags_);
  }
}
