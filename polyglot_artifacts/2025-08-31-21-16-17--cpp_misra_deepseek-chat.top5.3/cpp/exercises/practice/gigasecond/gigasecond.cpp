#include "gigasecond.h"
#include <cstdint>

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& start) {
    // Define the number of seconds in a gigasecond using a fixed-width integer
    const std::int64_t gigasecond_seconds = 1000000000;
    // Add the duration to the start time
    return start + boost::posix_time::seconds(gigasecond_seconds);
}

}  // namespace gigasecond
