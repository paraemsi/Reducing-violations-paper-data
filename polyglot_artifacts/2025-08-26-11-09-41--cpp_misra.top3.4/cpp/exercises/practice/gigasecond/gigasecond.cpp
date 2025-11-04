#include "gigasecond.h"
#include <cstdint>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

time_point advance(const time_point& start)
{
    // 1 gigasecond = 1,000,000,000 seconds
    // Use Boost's time_duration for addition
    constexpr std::int64_t gigasecond_value = static_cast<std::int64_t>(1000000000);
    return (start + boost::posix_time::seconds(gigasecond_value));
}

}  // namespace gigasecond
