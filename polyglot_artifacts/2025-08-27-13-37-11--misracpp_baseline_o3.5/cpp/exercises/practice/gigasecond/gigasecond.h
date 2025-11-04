#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

/*
 * Return the supplied time_point advanced by exactly one gigasecond
 * (1 000 000 000 seconds).
 */
//
// The interface uses boost::posix_time::ptime because the exercise’s
// canonical tests are written with Boost Date-Time utilities
// (time_from_string, seconds, etc.).  Using the same type eliminates any
// implicit conversions and keeps the public API consistent with the tests.
boost::posix_time::ptime advance(const boost::posix_time::ptime& tp);

}  // namespace gigasecond

#endif // GIGASECOND_H
