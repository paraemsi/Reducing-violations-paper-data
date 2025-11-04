#include "gigasecond.h"
#include <cstdint>

namespace gigasecond {

auto advance(boost::posix_time::ptime const& t)
    -> boost::posix_time::ptime {
    /* std::chrono provides strong typing for representing durations and
     * time points.  Adding the required duration yields the requested
     * gigasecond anniversary.
     */
    /* Add exactly 1 000 000 000 s (one gigasecond) using Boost date-time.   */
    return (t + boost::posix_time::seconds(static_cast<std::int64_t>(1000000000)));
}

}  // namespace gigasecond
