#include "gigasecond.h"

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& time) {
    // Add 1,000,000,000 seconds to the input time
    using namespace boost::posix_time;
    return time + seconds(1000000000);
}

}  // namespace gigasecond
