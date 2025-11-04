#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& start) {
    // Add one gigasecond (1,000,000,000 seconds) to the start time
    // Use a fixed-width integer type according to the rules
    const std::int64_t giga_sec = 1000000000;
    return start + boost::posix_time::seconds(giga_sec);
}

}  // namespace gigasecond
