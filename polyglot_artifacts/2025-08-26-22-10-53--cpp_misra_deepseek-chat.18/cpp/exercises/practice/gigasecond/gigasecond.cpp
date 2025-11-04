#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& start) {
    // Add one gigasecond (1,000,000,000 seconds) to the start time
    // Using Boost's time_duration with a fixed-width integer type
    const std::int64_t gigasecond = static_cast<std::int64_t>(1000000000);
    return start + boost::posix_time::seconds(gigasecond);
}

}  // namespace gigasecond
