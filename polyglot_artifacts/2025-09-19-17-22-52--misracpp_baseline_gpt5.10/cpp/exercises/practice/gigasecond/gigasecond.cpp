#include "gigasecond.h"

namespace gigasecond {

boost::posix_time::ptime advance(boost::posix_time::ptime tp) {
    using namespace boost::posix_time;
    return tp + seconds(1000000000);
}

}  // namespace gigasecond
