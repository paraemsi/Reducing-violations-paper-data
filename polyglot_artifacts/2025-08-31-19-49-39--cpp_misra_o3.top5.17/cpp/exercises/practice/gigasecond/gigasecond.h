#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

// Returns the time point that is exactly one gigasecond after the input.
auto advance(const boost::posix_time::ptime& start) -> boost::posix_time::ptime;

}  // namespace gigasecond

#endif // GIGASECOND_H
