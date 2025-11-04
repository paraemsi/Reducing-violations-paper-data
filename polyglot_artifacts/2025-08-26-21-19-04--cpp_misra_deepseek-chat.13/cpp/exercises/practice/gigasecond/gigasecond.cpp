#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& start) {
    // Define the number of seconds using a fixed-width integer type
    constexpr std::int64_t gigasecond = 1000000000;
    // Add one gigasecond, casting to the appropriate type expected by seconds()
    return start + boost::posix_time::seconds(static_cast<long>(gigasecond));
}

}  // namespace gigasecond
