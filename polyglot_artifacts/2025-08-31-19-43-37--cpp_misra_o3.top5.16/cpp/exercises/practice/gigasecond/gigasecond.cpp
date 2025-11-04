#include "gigasecond.h"
#include <cstdint>

namespace gigasecond {


/* One gigasecond expressed in seconds (1 000 000 000). */
constexpr std::int64_t kGigasecond{ 1000000000 };

/**
 * @brief Returns the time-point occurring one gigasecond after @p start.
 */
time_point advance(const time_point& start)
{
    /* Explicit cast satisfies MISRA rule on deliberate conversions. */
    return start + boost::posix_time::seconds(static_cast<long>(kGigasecond));
}

}  // namespace gigasecond
