#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

const boost::posix_time::time_duration
    giga_second{boost::posix_time::seconds(1'000'000'000)};

auto advance(boost::posix_time::ptime const& tp) -> boost::posix_time::ptime
{
    return tp + giga_second;
}

}  // namespace gigasecond
