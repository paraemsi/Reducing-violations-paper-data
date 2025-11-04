#if !defined(GIGASECOND_H)
#define GIGASECOND_H
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

/* The length of one gigasecond expressed as a chrono duration.
 * `inline` avoids multiple definition errors across translation units. */
/* One gigasecond expressed as a Boost time_duration. */
extern const boost::posix_time::time_duration giga_second;

/* Return the time point occurring exactly one gigasecond after the input. */
auto advance(boost::posix_time::ptime const& tp) -> boost::posix_time::ptime;

}  // namespace gigasecond

#endif // GIGASECOND_H
