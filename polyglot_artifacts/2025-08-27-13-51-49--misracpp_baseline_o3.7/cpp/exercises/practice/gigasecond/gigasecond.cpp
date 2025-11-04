#include "gigasecond.h"

namespace gigasecond {

const boost::posix_time::seconds gigasecond_duration(1000000000);

boost::posix_time::ptime advance(const boost::posix_time::ptime& tp) {
    return tp + gigasecond_duration;
}

}  // namespace gigasecond
