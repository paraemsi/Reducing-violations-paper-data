#include "gigasecond.h"

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& tp) {
    return tp + gigasecond_span;
}

}  // namespace gigasecond
