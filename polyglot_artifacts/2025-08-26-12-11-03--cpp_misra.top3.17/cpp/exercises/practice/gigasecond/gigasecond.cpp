#include "gigasecond.h"
#include <cstdint>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

time_point advance(const time_point& start)
{
    // 1 gigasecond = 1,000,000,000 seconds
    constexpr std::int64_t gigasecond = static_cast<std::int64_t>(1000000000);
    return (start + boost::posix_time::seconds(gigasecond));
}

}  // namespace gigasecond
