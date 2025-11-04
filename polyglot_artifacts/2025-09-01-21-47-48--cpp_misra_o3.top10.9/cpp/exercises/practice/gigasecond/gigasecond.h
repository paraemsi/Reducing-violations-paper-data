#if !defined(GIGASECOND_H)
#define GIGASECOND_H
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

/**
 * @brief Advance the given time point by one gigasecond (1 000 000 000 s).
 *
 * @param start The starting point in time.
 * @return The time point exactly one gigasecond later.
 */
auto advance(const boost::posix_time::ptime& start) -> boost::posix_time::ptime;

}  // namespace gigasecond

#endif // GIGASECOND_H
