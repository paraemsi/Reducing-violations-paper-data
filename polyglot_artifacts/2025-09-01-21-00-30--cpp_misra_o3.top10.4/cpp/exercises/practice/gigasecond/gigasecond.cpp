#include "gigasecond.h"

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& tp)
{
    // MISRA-compliant: add exactly one gigasecond using Boost date-time
    static constexpr boost::posix_time::seconds gigasecond{1000000000};
    return (tp + gigasecond);
}

}  // namespace gigasecond
