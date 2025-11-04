#include "gigasecond.h"

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& birth_time) {
    // Add one gigasecond (1,000,000,000 seconds) to the birth time
    return birth_time + boost::posix_time::seconds(1000000000);
}

}  // namespace gigasecond
