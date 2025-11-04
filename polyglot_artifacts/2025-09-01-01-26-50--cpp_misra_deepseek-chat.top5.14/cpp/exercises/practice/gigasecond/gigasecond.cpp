#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& start) {
    // Add one gigasecond (1,000,000,000 seconds) to the input time
    // Using boost::posix_time::seconds which can handle large durations
    // According to MISRA, we need to use fixed-width integer types
    // Use a literal that fits in int64_t
    const std::int64_t gigasecond = static_cast<std::int64_t>(1000000000);
    return start + boost::posix_time::seconds(gigasecond);
}

}  // namespace gigasecond
