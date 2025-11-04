#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& time) {
    // Create a duration of exactly 1,000,000,000 seconds
    boost::posix_time::time_duration gigasecond = boost::posix_time::seconds(1000000000);
    return time + gigasecond;
}

}  // namespace gigasecond
