#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

/* Alias matching the Boost test-suite expectations */
using sys_seconds = boost::posix_time::ptime;

/**
 * @brief Calculate the time point that is one gigasecond after the given start time.
 *
 * @param start A time point with second precision.
 * @return sys_seconds The time point exactly 1 000 000 000 seconds after \p start.
 */
auto advance(const sys_seconds& start) -> sys_seconds;

}  // namespace gigasecond

#endif // GIGASECOND_H
