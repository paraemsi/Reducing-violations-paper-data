#include "gigasecond.h"

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& start) noexcept
{
    /* Explicitly cast to boost::posix_time::time_duration::sec_type to avoid
     * implicit numeric conversion and comply with MISRA rules regarding
     * argument-parameter type matching. */
    return start + boost::posix_time::seconds(
        static_cast<boost::posix_time::time_duration::sec_type>(gigasecond));
}

}  // namespace gigasecond
