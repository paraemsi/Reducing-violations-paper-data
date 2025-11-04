#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

static const boost::posix_time::seconds gigasecond_offset{static_cast<std::int64_t>(1000000000)};

auto advance(const time_point& start) noexcept -> time_point
{
    return start + gigasecond_offset;
}

}  // namespace gigasecond
