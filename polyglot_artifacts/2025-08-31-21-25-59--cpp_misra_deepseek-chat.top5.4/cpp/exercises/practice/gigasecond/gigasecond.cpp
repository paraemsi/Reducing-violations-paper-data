#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& start) {
    // Add one gigasecond to the start time
    // A gigasecond is 1,000,000,000 seconds
    // Use a fixed-width integer type
    const std::int64_t gigasecond_seconds = 1000000000;
    // Create the duration using the integer value
    const boost::posix_time::time_duration gigasecond = 
        boost::posix_time::seconds(static_cast<long>(gigasecond_seconds));
    return (start + gigasecond);
}

}  // namespace gigasecond
