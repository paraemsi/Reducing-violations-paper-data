#include "gigasecond.h"

namespace gigasecond {

// Duration representing exactly one gigasecond (1 000 000 000 seconds)
const ::boost::posix_time::time_duration gigasecond_duration =
    ::boost::posix_time::seconds(static_cast<std::int64_t>(1000000000));


auto advance(const ::boost::posix_time::ptime& start)
    -> ::boost::posix_time::ptime
{
    return (start + gigasecond_duration);
}

}  // namespace gigasecond
