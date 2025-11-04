#include "gigasecond.h"
#include <cstdint>

namespace gigasecond {

time_point advance(const time_point& start)
{
    // 1 gigasecond = 1,000,000,000 seconds
    // Use std::int64_t for the count, per MISRA C++ rules
    constexpr std::int64_t gigasecond_count = static_cast<std::int64_t>(1000000000);
    return (start + std::chrono::seconds(gigasecond_count));
}

}  // namespace gigasecond
