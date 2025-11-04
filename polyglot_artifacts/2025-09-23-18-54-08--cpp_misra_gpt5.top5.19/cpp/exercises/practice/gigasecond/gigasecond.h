#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

#if defined(__has_cpp_attribute)
#  if __has_cpp_attribute(nodiscard)
#    define GIGASECOND_NODISCARD [[nodiscard]]
#  else
#    define GIGASECOND_NODISCARD
#  endif
#else
#  define GIGASECOND_NODISCARD
#endif

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& tp);

}  // namespace gigasecond

#endif // GIGASECOND_H
