#include "gigasecond.h"

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& start) noexcept
{
    // Add one gigasecond (1,000,000,000 seconds) to the input time_point.
    return (start + boost::posix_time::seconds(1000000000L));
}

}  // namespace gigasecond
