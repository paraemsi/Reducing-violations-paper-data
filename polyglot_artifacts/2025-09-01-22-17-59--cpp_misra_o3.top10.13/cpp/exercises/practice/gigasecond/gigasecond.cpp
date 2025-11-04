#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

namespace {
/* 1 000 000 000 seconds expressed as a chrono duration.
 * Using a constexpr object avoids re-creating the duration on each call.
 */
const boost::posix_time::time_duration gigasecond_duration =
    boost::posix_time::seconds(1'000'000'000L);
}  // unnamed namespace

auto advance(const boost::posix_time::ptime& start)
    -> boost::posix_time::ptime
{
    /* Addition is safe because both operands share the same chrono category.
     * No implicit narrowing or signedness change occurs.
     */
    return start + gigasecond_duration;
}


}  // namespace gigasecond
