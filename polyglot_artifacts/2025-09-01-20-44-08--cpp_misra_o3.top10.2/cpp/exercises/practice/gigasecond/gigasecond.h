#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <cstdint>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

/* Alias representing a Boost POSIX time point with second precision. */
using time_point = boost::posix_time::ptime;

/**
 * @brief Advance exactly one gigasecond (1 000 000 000 s) from the supplied
 *        time point.
 *
 * @param start  Time point to begin from (second precision).
 * @return time_point  Moment occurring precisely one gigasecond later.
 */
auto advance(const time_point& start) -> time_point;

}  // namespace gigasecond

#endif // GIGASECOND_H
