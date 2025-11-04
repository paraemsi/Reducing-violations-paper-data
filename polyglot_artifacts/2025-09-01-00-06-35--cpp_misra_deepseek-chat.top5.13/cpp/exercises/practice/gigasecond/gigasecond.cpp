#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& start) {
    // Define the gigasecond value using a fixed-width integer
    const std::int64_t gigasecond = 1000000000;
    // Add one gigasecond to the start time
    return start + boost::posix_time::seconds(gigasecond);
}

}  // namespace gigasecond
