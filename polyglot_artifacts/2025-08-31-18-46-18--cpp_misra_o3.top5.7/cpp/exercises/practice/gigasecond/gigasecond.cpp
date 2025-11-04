#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

static constexpr std::int64_t gigasecond_value{static_cast<std::int64_t>(1'000'000'000)};

boost::posix_time::ptime advance(const boost::posix_time::ptime& start)
{
    return start + boost::posix_time::seconds(static_cast<long>(gigasecond_value));
}

}  // namespace gigasecond
