#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

auto advance(const boost::posix_time::ptime& start)
    -> boost::posix_time::ptime
{
    /* One gigasecond is 1 000 000 000 seconds. */
    const boost::posix_time::seconds gigasecond(
        static_cast<std::int32_t>(1000000000));

    return start + gigasecond;
}

}  // namespace gigasecond
