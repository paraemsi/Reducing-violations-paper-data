#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& start) {
    // Add exactly 1,000,000,000 seconds
    using namespace boost::posix_time;
    static const time_duration giga_duration = seconds(1000000000);
    return start + giga_duration;
}

}  // namespace gigasecond
