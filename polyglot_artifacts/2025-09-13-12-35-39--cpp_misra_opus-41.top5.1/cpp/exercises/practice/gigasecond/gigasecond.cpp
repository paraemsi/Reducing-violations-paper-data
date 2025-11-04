#include "gigasecond.h"
#include <cstdint>

namespace gigasecond {
    boost::posix_time::ptime advance(const boost::posix_time::ptime& start_time) {
        const std::int64_t gigasecond = 1000000000;
        return start_time + boost::posix_time::seconds(gigasecond);
    }
}  // namespace gigasecond
