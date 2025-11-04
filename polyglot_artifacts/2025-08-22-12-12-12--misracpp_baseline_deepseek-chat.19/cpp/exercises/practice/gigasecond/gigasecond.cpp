#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& start) {
    // Use a long long to ensure no overflow
    return start + boost::posix_time::seconds(1000000000LL);
}

}  // namespace gigasecond
