#include "gigasecond.h"

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& start) {
    static const boost::posix_time::time_duration gigasecond = boost::posix_time::seconds(1000000000);
    return start + gigasecond;
}

}  // namespace gigasecond
