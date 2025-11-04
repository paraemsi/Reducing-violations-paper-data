#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

/*
 * Return the moment in time that is exactly one gigasecond
 * (1 000 000 000 seconds) after the supplied starting point.
 */
auto advance(const boost::posix_time::ptime& start)
    -> boost::posix_time::ptime;


}  // namespace gigasecond

#endif // GIGASECOND_H
