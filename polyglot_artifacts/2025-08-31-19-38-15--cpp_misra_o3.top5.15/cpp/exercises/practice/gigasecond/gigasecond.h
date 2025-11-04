#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

/*  Alias for the Boost ptime used by the exercism tests */
using time_point = boost::posix_time::ptime;

/**
 * @brief Add one gigasecond to the specified time point.
 *
 * @param t The starting time point.
 * @return time_point The time point exactly one gigasecond later.
 */
auto advance(time_point t) -> time_point;

}  // namespace gigasecond

#endif // GIGASECOND_H
