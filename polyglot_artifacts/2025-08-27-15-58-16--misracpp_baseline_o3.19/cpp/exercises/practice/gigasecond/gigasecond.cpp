#include "gigasecond.h"

namespace gigasecond {

time_point advance(const time_point& tp) {
    // One gigasecond = 1 000 000 000 seconds
    return tp + boost::posix_time::seconds(1'000'000'000);
}

}  // namespace gigasecond
