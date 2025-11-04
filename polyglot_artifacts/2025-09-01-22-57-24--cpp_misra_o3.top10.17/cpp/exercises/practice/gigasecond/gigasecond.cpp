#include "gigasecond.h"

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

auto advance(const boost::posix_time::ptime& moment)
    -> boost::posix_time::ptime
{
    // 1 000 000 000 s expressed exactly (use plain literal for C++11 compatibility)
    constexpr boost::posix_time::seconds gigasecond{1000000000L};

    return (moment + gigasecond);
}

}  // namespace gigasecond
