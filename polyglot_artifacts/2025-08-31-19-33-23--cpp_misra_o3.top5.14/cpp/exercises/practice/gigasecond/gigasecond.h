#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {


/**
 * @brief  Add one gigasecond to the supplied time-point.
 *
 * @param  start  The starting time-point.
 * @return A new time-point exactly one gigasecond after \p start.
 */
auto advance(const boost::posix_time::ptime& start)
    -> boost::posix_time::ptime;

}  // namespace gigasecond

#endif // GIGASECOND_H
