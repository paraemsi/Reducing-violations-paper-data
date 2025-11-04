#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

// One gigasecond expressed as a Boost time duration.
inline const boost::posix_time::seconds gigasecond{
    boost::posix_time::seconds{1'000'000'000}};

/*
 * Add one gigasecond to the supplied time point.
 *
 * @param tp  The starting time point expressed with second precision.
 * @return    A new time point exactly one gigasecond later.
 */
using ptime = boost::posix_time::ptime;

[[nodiscard]] auto advance(const ptime& tp) -> ptime;

}  // namespace gigasecond

#endif // GIGASECOND_H
