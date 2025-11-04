#include "gigasecond.h"

namespace {
const boost::posix_time::time_duration k_gigasecond = boost::posix_time::seconds(1000000000);
}

namespace gigasecond {

boost::posix_time::ptime add(const boost::posix_time::ptime& tp) noexcept {
    return (tp + k_gigasecond);
}

boost::posix_time::ptime advance(const boost::posix_time::ptime& tp) noexcept {
    return add(tp);
}

}  // namespace gigasecond
