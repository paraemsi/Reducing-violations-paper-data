#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

// Type aliases to make the public interface clearer.
using time_point = boost::posix_time::ptime;

/**
 * Return a time_point exactly one gigasecond (1 000 000 000 s)
 * after the supplied time_point.
 */
time_point advance(time_point tp);

}  // namespace gigasecond

#endif // GIGASECOND_H
