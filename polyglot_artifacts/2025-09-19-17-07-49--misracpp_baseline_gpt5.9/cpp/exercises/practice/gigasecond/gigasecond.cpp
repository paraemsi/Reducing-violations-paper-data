#include "gigasecond.h"

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& tp) {
    return tp + boost::posix_time::seconds(1000000000);
}

}  // namespace gigasecond
