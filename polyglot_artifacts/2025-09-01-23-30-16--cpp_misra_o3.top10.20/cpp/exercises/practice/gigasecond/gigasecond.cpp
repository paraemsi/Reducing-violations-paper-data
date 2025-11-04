#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

GIGASECOND_NODISCARD boost::posix_time::ptime add(
    const boost::posix_time::ptime& start)
{
    // One gigasecond expressed using a fixed-width type to respect MISRA C++.
    constexpr std::int64_t giga_value{1'000'000'000};
    const boost::posix_time::seconds gigasecond_duration{
        static_cast<boost::posix_time::seconds::sec_type>(giga_value)};

    return start + gigasecond_duration;
}

GIGASECOND_NODISCARD boost::posix_time::ptime advance(
    const boost::posix_time::ptime& start)
{
    /* Delegate to add() to maintain a single implementation. */
    return add(start);
}

}  // namespace gigasecond
