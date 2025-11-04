#include "gigasecond.h"

#include <chrono>

namespace gigasecond {

auto advance(const std::chrono::system_clock::time_point& start_time)
    -> std::chrono::system_clock::time_point
{
    /* 1 000 000 000 s represented with the exact type used by
     * std::chrono::seconds to avoid implicit conversions.
     */
    constexpr std::chrono::seconds::rep k_one_gigasecond_rep{
        static_cast<std::chrono::seconds::rep>(1'000'000'000)
    };

    /* Advance the time-point by one gigasecond. */
    return start_time + std::chrono::seconds{k_one_gigasecond_rep};
}

}  // namespace gigasecond
