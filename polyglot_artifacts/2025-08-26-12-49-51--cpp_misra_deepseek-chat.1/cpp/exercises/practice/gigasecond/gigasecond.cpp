#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& start) {
    // Use a fixed-width integer type for the gigasecond count
    const std::int64_t gigasecond_seconds = 1000000000;
    // Add one gigasecond to the start time
    return start + boost::posix_time::seconds(gigasecond_seconds);
}

}  // namespace gigasecond
