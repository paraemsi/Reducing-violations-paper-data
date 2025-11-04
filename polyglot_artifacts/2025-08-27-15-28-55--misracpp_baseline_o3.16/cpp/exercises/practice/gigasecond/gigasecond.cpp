#include "gigasecond.h"

namespace gigasecond {

const boost::posix_time::time_duration gigasecond_duration =
    boost::posix_time::seconds(1'000'000'000);

time_point advance(time_point point) {
    return point + gigasecond_duration;
}

}  // namespace gigasecond
