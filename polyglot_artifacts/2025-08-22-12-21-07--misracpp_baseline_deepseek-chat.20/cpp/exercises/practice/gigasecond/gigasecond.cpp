#include "gigasecond.h"

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& birth_time) {
    // Add one gigasecond (1,000,000,000 seconds)
    const boost::posix_time::time_duration gigasecond = 
        boost::posix_time::seconds(1000000000LL);
    return birth_time + gigasecond;
}

}  // namespace gigasecond
