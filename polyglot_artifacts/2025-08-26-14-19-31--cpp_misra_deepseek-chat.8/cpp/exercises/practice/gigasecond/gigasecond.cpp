#include "gigasecond.h"
#include <cstdint>

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& start) {
    // Add one gigasecond (1,000,000,000 seconds)
    // Use a fixed-width integer type according to MISRA rules
    const std::int64_t gigasecond_seconds = 1000000000;
    const boost::posix_time::time_duration gigasecond = 
        boost::posix_time::seconds(gigasecond_seconds);
    return start + gigasecond;
}

}  // namespace gigasecond
