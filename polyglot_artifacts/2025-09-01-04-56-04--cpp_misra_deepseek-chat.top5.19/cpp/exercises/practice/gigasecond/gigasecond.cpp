#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

boost::posix_time::ptime advance(boost::posix_time::ptime start) {
    // Add one gigasecond which is 1,000,000,000 seconds
    // Using boost::posix_time::seconds which can handle this duration
    // Use a fixed-width integer type to follow the rules
    const std::int64_t gigasecond = 1000000000;
    return start + boost::posix_time::seconds(static_cast<boost::posix_time::time_duration::sec_type>(gigasecond));
}

}  // namespace gigasecond
