#include "gigasecond.h"

namespace gigasecond {

    boost::posix_time::ptime advance(const boost::posix_time::ptime& time) {
        return time + boost::posix_time::seconds(1000000000L);
    }

}  // namespace gigasecond
