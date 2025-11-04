#include "gigasecond.h"
#include <cstdint>

namespace gigasecond {

time_point add_gigasecond(const time_point& start)
{
    constexpr std::int64_t gigasecond_value = static_cast<std::int64_t>(1000000000);
    return (start + std::chrono::seconds(gigasecond_value));
}

// For test compatibility, provide the expected function name 'advance'
time_point advance(const time_point& start)
{
    return add_gigasecond(start);
}

}  // namespace gigasecond
