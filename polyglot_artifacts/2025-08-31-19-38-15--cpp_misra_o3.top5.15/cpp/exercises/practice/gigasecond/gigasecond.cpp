#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

namespace {

constexpr std::int64_t giga_seconds_val{1'000'000'000};

const boost::posix_time::seconds gigasecond_duration{
    static_cast<long>(giga_seconds_val)};

}  // unnamed namespace

auto advance(time_point t) -> time_point
{
    return (t + gigasecond_duration);
}

}  // namespace gigasecond
