#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

time_point advance(const time_point& start) {
    // Add one gigasecond (1,000,000,000 seconds)
    const std::int64_t gigasecond = static_cast<std::int64_t>(1000000000LL);
    return start + boost::posix_time::seconds(gigasecond);
}

}  // namespace gigasecond
