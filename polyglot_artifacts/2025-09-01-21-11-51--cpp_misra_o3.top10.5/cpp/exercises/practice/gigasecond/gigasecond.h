#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

/*  Alias for a Boost posix_time time-point (ptime).
 *  This matches the type used by the Exercism test-suite while
 *  keeping the public interface concise.
 */
using time_point = boost::posix_time::ptime;

/*  Return the moment that occurs exactly one gigasecond
 *  (1 000 000 000 seconds) after the supplied time_point.          */
[[nodiscard]] time_point advance(const time_point& start_time);

}  // namespace gigasecond

#endif // GIGASECOND_H
