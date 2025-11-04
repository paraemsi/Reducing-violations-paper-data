#include "gigasecond.h"

namespace gigasecond {

static const boost::posix_time::time_duration gigasecond_duration =
        boost::posix_time::seconds(1000000000);

/**
 * Return the supplied time_point advanced by one gigasecond.
 */
time_point advance(const time_point& tp) {
    return tp + gigasecond_duration;
}

}  // namespace gigasecond
