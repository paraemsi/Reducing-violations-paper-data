#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

// Returns the instant that is exactly one gigasecond (1 000 000 000 s)
// after the provided time point.
[[nodiscard]] auto advance(const boost::posix_time::ptime& start)
    -> boost::posix_time::ptime;

}  // namespace gigasecond

#endif // GIGASECOND_H
