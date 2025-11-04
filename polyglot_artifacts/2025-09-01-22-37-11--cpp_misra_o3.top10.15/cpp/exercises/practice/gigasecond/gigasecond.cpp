#include "gigasecond.h"
#include <cstdint>

namespace gigasecond {

auto advance(time_point const& start) -> time_point
{
    /* One gigasecond expressed as a signed 64-bit integer. */
    constexpr std::int64_t gigasecond_value{static_cast<std::int64_t>(1000000000)};

    /* Duration representing one gigasecond. */
    const boost::posix_time::seconds gigasecond_duration{static_cast<long>(gigasecond_value)};

    return (start + gigasecond_duration);
}

}  // namespace gigasecond
