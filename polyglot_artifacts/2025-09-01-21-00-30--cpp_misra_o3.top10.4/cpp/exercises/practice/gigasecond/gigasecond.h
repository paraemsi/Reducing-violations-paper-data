#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

// Adds exactly one gigasecond (1 000 000 000 s) to the supplied
// boost::posix_time::ptime.
boost::posix_time::ptime advance(const boost::posix_time::ptime& tp);

}  // namespace gigasecond

#endif // GIGASECOND_H
