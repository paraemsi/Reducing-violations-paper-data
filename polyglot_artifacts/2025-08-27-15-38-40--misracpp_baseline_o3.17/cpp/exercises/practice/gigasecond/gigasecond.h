#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

using boost::posix_time::ptime;

inline constexpr long GIGASECOND = 1'000'000'000L;

/**
 * Return the time point exactly one gigasecond after the supplied time.
 */
ptime advance(const ptime& pt);

}  // namespace gigasecond

#endif // GIGASECOND_H
