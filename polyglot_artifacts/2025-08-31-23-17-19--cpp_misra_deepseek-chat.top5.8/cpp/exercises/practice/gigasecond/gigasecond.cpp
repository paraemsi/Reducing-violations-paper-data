#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& time) {
    // Add one gigasecond (1,000,000,000 seconds)
    // Use a fixed-width integer type according to MISRA rules
    constexpr std::int64_t gigasecond = 1000000000;
    
    // Check if the value fits in a long to ensure no narrowing
    // Since long is at least 32 bits, and 1,000,000,000 fits in 32 bits, this is safe
    static_assert(gigasecond <= static_cast<std::int64_t>((1LL << 31) - 1), 
                  "gigasecond value too large for long type");
    
    // Create a time duration of one gigasecond
    // The seconds() function expects a long, so we need to cast
    // This cast is safe due to the static_assert above
    const long gigasecond_long = static_cast<long>(gigasecond);
    boost::posix_time::time_duration gigasecond_duration = 
        boost::posix_time::seconds(gigasecond_long);
    
    // Add the duration to the input time
    return time + gigasecond_duration;
}

}  // namespace gigasecond
