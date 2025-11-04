#include "gigasecond.h"

namespace gigasecond {

static const boost::posix_time::time_duration gigasecond_span =
    boost::posix_time::seconds(1'000'000'000);

/**
 * Add one gigasecond to the given time_point.
 */
time_point advance(time_point tp) {
    return tp + gigasecond_span;
}

}  // namespace gigasecond
