#include "gigasecond.h"
#include <cstdint>

namespace gigasecond {

boost::posix_time::ptime advance(boost::posix_time::ptime start) {
    // Add one gigasecond (1,000,000,000 seconds) to the start time
    // Use a fixed-width integer type
    const std::int64_t gigasecond = 1000000000;
    return start + boost::posix_time::seconds(gigasecond);
}

}  // namespace gigasecond
