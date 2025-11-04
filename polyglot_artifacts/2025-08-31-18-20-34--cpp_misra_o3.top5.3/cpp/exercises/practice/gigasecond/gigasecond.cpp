#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& start) noexcept
{
    static const boost::posix_time::time_duration gigasecond_duration =
        boost::posix_time::seconds(1000000000);  // 1 000 000 000 s

    return (start + gigasecond_duration);
}

}  // namespace gigasecond
