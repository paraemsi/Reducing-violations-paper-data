#include "gigasecond.h"

namespace gigasecond {
    boost::posix_time::ptime advance(const boost::posix_time::ptime& time) {
        // One gigasecond is 1,000,000,000 seconds
        boost::posix_time::seconds gigasecond(1000000000);
        return time + gigasecond;
    }
}  // namespace gigasecond
