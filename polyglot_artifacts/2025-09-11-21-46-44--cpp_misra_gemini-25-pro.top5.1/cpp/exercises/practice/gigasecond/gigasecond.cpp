#include "gigasecond.h"
#include <cstdint>

namespace gigasecond {

using boost::posix_time::ptime;
using boost::posix_time::seconds;

ptime advance(const ptime& start_time) {
    constexpr std::int32_t gigasecond_in_seconds = 1000000000;
    return (start_time + seconds(gigasecond_in_seconds));
}

}  // namespace gigasecond
