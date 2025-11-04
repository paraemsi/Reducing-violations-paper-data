#include "gigasecond.h"

namespace gigasecond {

namespace {
/* 1 000 000 000 s represented as a Boost time_duration object produced via the
 * helper factory boost::posix_time::seconds().  The object must be ‘static’
 * (not constexpr) because the Boost factory is not constexpr-capable.
 */
static const boost::posix_time::time_duration gigasecond_duration =
    boost::posix_time::seconds(1'000'000'000);
}  // unnamed namespace

auto advance(const sys_seconds& start) -> sys_seconds
{
    return start + gigasecond_duration;
}

}  // namespace gigasecond
