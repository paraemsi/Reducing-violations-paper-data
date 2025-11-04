#include "gigasecond.h"

namespace gigasecond {

    const boost::posix_time::time_duration GIGASECOND = boost::posix_time::seconds(1'000'000'000);

    boost::posix_time::ptime advance(const boost::posix_time::ptime& start) {
        return start + GIGASECOND;
    }

}  // namespace gigasecond
