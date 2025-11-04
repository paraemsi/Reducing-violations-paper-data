#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& start) {
    // Add 1,000,000,000 seconds to the start time
    // Use a fixed-width type to ensure portability
    const std::int64_t gigasecond = 1000000000;
    return start + boost::posix_time::seconds(gigasecond);
}

}  // namespace gigasecond
