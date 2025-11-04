#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

auto advance(const boost::posix_time::ptime& pt) -> boost::posix_time::ptime
{
    static const boost::posix_time::time_duration gigasecond_duration =
        boost::posix_time::seconds(1'000'000'000);

    return pt + gigasecond_duration;
}

}  // namespace gigasecond
