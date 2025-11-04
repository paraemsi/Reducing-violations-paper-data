#include "gigasecond.h"

namespace gigasecond {

GIGASECOND_NODISCARD boost::posix_time::ptime advance(boost::posix_time::ptime const& time_point) noexcept
{
    /* Add exactly one gigasecond (1 000 000 000 s) */
    return time_point + boost::posix_time::seconds(
        static_cast<boost::posix_time::time_duration::sec_type>(1000000000)
    );
}

}  // namespace gigasecond
