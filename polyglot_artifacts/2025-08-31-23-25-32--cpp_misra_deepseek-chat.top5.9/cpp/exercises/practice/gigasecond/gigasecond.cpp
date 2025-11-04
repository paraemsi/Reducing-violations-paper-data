#include "gigasecond.h"
#include <ctime>
#include <cstdint>

namespace gigasecond {

struct tm advance(struct tm start) {
    // Convert tm to time_t
    // Set daylight saving time flag to not available
    start.tm_isdst = -1;
    std::time_t time = std::mktime(&start);
    
    // Add one gigasecond (1,000,000,000 seconds)
    // Use a fixed-width integer type
    const std::int64_t gigasecond = 1000000000;
    time += gigasecond;
    
    // Convert back to tm struct
    // Use localtime to get the result in local time
    struct tm* result = std::localtime(&time);
    return *result;
}

}  // namespace gigasecond
