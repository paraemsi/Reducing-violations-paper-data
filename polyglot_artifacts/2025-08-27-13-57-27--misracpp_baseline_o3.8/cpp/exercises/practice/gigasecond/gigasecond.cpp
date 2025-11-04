#include "gigasecond.h"

namespace gigasecond {

const boost::posix_time::time_duration gigasecond_duration =
    boost::posix_time::seconds(1000000000);

boost::posix_time::ptime advance(const boost::posix_time::ptime& start) {
    return start + gigasecond_duration;
}

}  // namespace gigasecond
