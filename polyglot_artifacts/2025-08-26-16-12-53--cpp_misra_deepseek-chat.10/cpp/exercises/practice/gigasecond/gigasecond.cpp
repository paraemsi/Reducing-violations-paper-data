#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& start) {
    // Define the gigasecond using a fixed-width type
    const std::int64_t gigasecond_seconds = static_cast<std::int64_t>(1000000000);
    // Add one gigasecond to the start time
    return start + boost::posix_time::seconds(gigasecond_seconds);
}

}  // namespace gigasecond
