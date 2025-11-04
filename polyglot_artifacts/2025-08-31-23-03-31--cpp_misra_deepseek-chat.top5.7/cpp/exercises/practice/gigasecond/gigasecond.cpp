#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& start) {
    // Add one gigasecond (1,000,000,000 seconds) to the start time
    // Use a fixed-width integer type
    const std::int64_t gigasecond = 1000000000LL;
    // Use boost's time_duration to add the seconds
    // The addition operation is between compatible types (ptime and time_duration)
    // which should be fine according to the rules
    return start + boost::posix_time::seconds(gigasecond);
}

}  // namespace gigasecond
