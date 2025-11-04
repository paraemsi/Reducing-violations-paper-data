#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

boost::posix_time::ptime advance(
    const boost::posix_time::ptime& tp) noexcept
{
    /* One gigasecond equals 1 000 000 000 seconds. */
    const boost::posix_time::seconds gigasecond{1000000000};

    return tp + gigasecond;
}

}  // namespace gigasecond
