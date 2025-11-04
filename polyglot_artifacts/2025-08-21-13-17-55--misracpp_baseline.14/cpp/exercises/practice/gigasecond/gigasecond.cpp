#include "gigasecond.h"

namespace gigasecond {

const long GIGASECOND = 1000000000L;

boost::posix_time::ptime advance(const boost::posix_time::ptime& tp) {
    return tp + boost::posix_time::seconds(GIGASECOND);
}

}  // namespace gigasecond
