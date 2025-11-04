#include "gigasecond.h"

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& start) {
    using namespace boost::posix_time;
    static const seconds gigasecond(1000000000);
    return start + gigasecond;
}

}  // namespace gigasecond
