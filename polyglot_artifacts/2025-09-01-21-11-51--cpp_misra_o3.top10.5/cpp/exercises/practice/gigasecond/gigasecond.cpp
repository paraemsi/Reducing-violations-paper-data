#include "gigasecond.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

[[nodiscard]] time_point advance(const time_point& start_time)
{
    /*  Add exactly one gigasecond (1 000 000 000 seconds) to the supplied
     *  time-point. The explicit cast prevents implicit integral promotion
     *  and keeps us compliant with the MISRA numeric-conversion rules.   */
    /*  Construct the constant once to avoid magic numbers in the
     *  expression and keep the arithmetic readable.                */
    constexpr boost::posix_time::time_duration gigasec{
        boost::posix_time::seconds(1'000'000'000L)};

    return (start_time + gigasec);
}

}  // namespace gigasecond
