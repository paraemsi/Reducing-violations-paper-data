#include "gigasecond.h"
#include <cstdint>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

time_point advance(const time_point& start)
{
    // 1_000_000_000 seconds in a gigasecond
    // boost::posix_time::seconds takes int, so we split into two adds if needed
    // But 1_000_000_000 fits in a 32-bit signed int, so it's safe
    return (start + boost::posix_time::seconds(1000000000));
}

}  // namespace gigasecond
