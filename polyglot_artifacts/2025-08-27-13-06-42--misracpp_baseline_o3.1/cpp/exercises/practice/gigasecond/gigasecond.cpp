#include "gigasecond.h"

namespace gigasecond {

time_point advance(const time_point& tp) {
    return tp + boost::posix_time::seconds{1'000'000'000};
}

}  // namespace gigasecond
