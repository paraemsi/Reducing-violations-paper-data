#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

/*  Alias to a Boost ptime representing a wall-clock moment with second precision. */
using time_point = boost::posix_time::ptime;

/*  Return the instant that is exactly one gigasecond after `start`. */
auto advance(const time_point& start) -> time_point;

}  // namespace gigasecond

#endif // GIGASECOND_H
