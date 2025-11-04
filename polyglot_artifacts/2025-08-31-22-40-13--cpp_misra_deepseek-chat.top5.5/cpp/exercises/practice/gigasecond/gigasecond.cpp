#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& start) {
    // Add one gigasecond (1,000,000,000 seconds) to the start time
    // Use a fixed-width integer type to follow MISRA rules
    // Make sure the literal is treated as int64_t to prevent potential overflow
    const std::int64_t gigasecond = static_cast<std::int64_t>(1000000000);
    // Create the duration using seconds
    boost::posix_time::seconds duration(gigasecond);
    return start + duration;
}

}  // namespace gigasecond
