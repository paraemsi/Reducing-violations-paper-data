#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

using time_point = boost::posix_time::ptime;

/**
 * Return the time point exactly one gigasecond after the given time point.
 */
time_point advance(const time_point& tp);

}  // namespace gigasecond

#endif // GIGASECOND_H
