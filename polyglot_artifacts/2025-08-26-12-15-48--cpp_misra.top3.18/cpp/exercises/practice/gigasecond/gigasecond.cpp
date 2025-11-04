#include "gigasecond.h"

namespace gigasecond {

time_point advance(const time_point& start)
{
    // 1 gigasecond = 1,000,000,000 seconds
    return (start + boost::posix_time::seconds(1000000000));
}

}  // namespace gigasecond
