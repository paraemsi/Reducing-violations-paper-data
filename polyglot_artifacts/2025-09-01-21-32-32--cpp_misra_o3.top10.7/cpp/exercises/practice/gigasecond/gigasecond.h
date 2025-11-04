#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

/*  Return the instant that is exactly one gigasecond (1 000 000 000 s)
    after the supplied time-point.  The caller should use the resulting
    value; to remain compatible with pre-C++17 builds, the [[nodiscard]]
    attribute is omitted. */
[[nodiscard]] boost::posix_time::ptime advance(boost::posix_time::ptime start);

}  // namespace gigasecond

#endif // GIGASECOND_H
