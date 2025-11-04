#include "gigasecond.h"

namespace gigasecond {

const boost::posix_time::time_duration gigasecond_duration =
    boost::posix_time::seconds(1000000000);

ptime advance(ptime tp) {
    return tp + gigasecond_duration;
}

}  // namespace gigasecond
