#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& start) {
    // Add one gigasecond (1,000,000,000 seconds) to the start time
    static const boost::posix_time::seconds giga_second(1000000000);
    return start + giga_second;
}

}  // namespace gigasecond
