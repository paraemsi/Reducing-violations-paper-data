#include "gigasecond.h"

namespace gigasecond {

auto advance(const std::chrono::system_clock::time_point& start)
    -> std::chrono::system_clock::time_point
{
    /*  A gigasecond expressed as a 64-bit signed integer.  */
    constexpr std::int64_t GIGASECOND{1'000'000'000};

    /*  Construct a duration of exactly one gigasecond.  */
    const std::chrono::seconds gigasec{GIGASECOND};

    return start + gigasec;
}

}  // namespace gigasecond
