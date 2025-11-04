#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

using time_point = boost::posix_time::ptime;

extern const boost::posix_time::time_duration gigasecond_duration;

/**
 * Return the point in time that is exactly one gigasecond after `point`.
 */
time_point advance(time_point point);

}  // namespace gigasecond

#endif // GIGASECOND_H
