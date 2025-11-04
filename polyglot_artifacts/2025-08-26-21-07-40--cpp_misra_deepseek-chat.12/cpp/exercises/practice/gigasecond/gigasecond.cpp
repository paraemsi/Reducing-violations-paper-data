#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& start) {
    // Add one gigasecond which is 1,000,000,000 seconds
    // Using Boost's time_duration to handle the addition
    // Use a fixed-width integer type to follow MISRA rules
    const std::int64_t giga_seconds = 1000000000;
    const boost::posix_time::time_duration gigasecond = 
        boost::posix_time::seconds(static_cast<long>(giga_seconds));
    return start + gigasecond;
}

}  // namespace gigasecond
