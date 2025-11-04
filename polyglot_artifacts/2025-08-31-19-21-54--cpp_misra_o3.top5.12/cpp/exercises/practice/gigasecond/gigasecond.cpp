#include "gigasecond.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace
{
    // One gigasecond expressed as a constant of type std::int64_t to meet MISRA
    // fixed-width integer requirements.
    constexpr std::int64_t gigasecond_value{ 1'000'000'000 };
}  // unnamed namespace

namespace gigasecond {

auto advance(const boost::posix_time::ptime& start)
    -> boost::posix_time::ptime
{
    const auto delta{ boost::posix_time::seconds(static_cast<long>(gigasecond_value)) };
    return (start + delta);
}

}  // namespace gigasecond
