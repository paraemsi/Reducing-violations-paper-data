#include "gigasecond.h"

namespace gigasecond {

constexpr boost::posix_time::time_duration gigasecond_duration{
    boost::posix_time::seconds(1'000'000'000)};

boost::posix_time::ptime advance(const boost::posix_time::ptime& time_point) {
    return time_point + gigasecond_duration;
}

}  // namespace gigasecond
