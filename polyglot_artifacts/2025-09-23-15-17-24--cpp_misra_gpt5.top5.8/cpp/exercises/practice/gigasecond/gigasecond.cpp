#include "gigasecond.h"
#include <cstdint>

namespace {
constexpr std::int64_t k_gigasecond = static_cast<std::int64_t>(1000000000);
}

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& start)
{
    const boost::posix_time::time_duration offset = boost::posix_time::seconds(k_gigasecond);
    return (start + offset);
}

}  // namespace gigasecond
