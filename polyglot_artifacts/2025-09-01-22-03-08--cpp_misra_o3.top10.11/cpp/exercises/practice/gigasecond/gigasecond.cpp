#include "gigasecond.h"
#include <cstdint>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

namespace {
    // The duration of one gigasecond expressed as a boost::posix_time::seconds constant.
    constexpr std::int64_t gigasecond_value{1'000'000'000};
    /* 1 gigasecond expressed as a Boost time duration.
       Cast through Boost’s own sec_type to avoid using a built-in
       integer type name directly (MISRA compliance). */
    const boost::posix_time::seconds gs_duration{
        boost::posix_time::seconds(
            static_cast<boost::posix_time::time_duration::sec_type>(gigasecond_value))};
} // unnamed namespace for internal linkage

auto advance(const ptime& start) -> ptime
{
    return (start + gs_duration);
}

} // namespace gigasecond
