#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& start) {
    // Add one gigasecond (1,000,000,000 seconds) to the start time
    const std::int64_t gigasecond = 1000000000;
    const boost::posix_time::time_duration duration = boost::posix_time::seconds(gigasecond);
    return (start + duration);
}

}  // namespace gigasecond
