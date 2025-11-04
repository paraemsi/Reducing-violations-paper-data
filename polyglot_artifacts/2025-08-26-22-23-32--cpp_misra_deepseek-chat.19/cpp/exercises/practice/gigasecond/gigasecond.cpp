#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

boost::posix_time::ptime advance(boost::posix_time::ptime start) {
    // Add one gigasecond (1,000,000,000 seconds) to the start time
    // Using boost::posix_time::seconds which can handle large values
    const std::int64_t gigasecond = static_cast<std::int64_t>(1000000000);
    return start + boost::posix_time::seconds(gigasecond);
}

}  // namespace gigasecond
