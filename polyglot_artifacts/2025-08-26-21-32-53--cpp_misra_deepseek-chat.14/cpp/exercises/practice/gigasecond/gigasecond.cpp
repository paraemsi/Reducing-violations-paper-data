#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& time) {
    // To follow the rules, explicitly cast the integer literal to std::int64_t
    const std::int64_t gigasecond = static_cast<std::int64_t>(1000000000);
    // Create a time duration from the number of seconds
    // The addition operation is handled by Boost, which should be fine
    boost::posix_time::time_duration duration = boost::posix_time::seconds(gigasecond);
    // Add the duration to the input time
    return time + duration;
}

}  // namespace gigasecond
