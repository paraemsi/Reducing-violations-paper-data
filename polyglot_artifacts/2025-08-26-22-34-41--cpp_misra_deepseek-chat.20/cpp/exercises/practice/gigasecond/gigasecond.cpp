#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& start) {
    // Add one gigasecond (1,000,000,000 seconds)
    // Use fixed-width integer type
    const std::int64_t giga_seconds = 1000000000;
    const boost::posix_time::time_duration giga_second = 
        boost::posix_time::seconds(giga_seconds);
    return start + giga_second;
}

}  // namespace gigasecond
