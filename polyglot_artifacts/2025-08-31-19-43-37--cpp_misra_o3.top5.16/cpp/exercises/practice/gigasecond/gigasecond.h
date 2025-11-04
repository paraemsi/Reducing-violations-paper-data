#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

using time_point = boost::posix_time::ptime;

/**
 * @brief Advance the supplied time-point by one gigasecond.
 *
 * @param start The starting point in time.
 * @return time_point The moment exactly one gigasecond later.
 */
time_point advance(const time_point& start);

}  // namespace gigasecond

#endif // GIGASECOND_H
