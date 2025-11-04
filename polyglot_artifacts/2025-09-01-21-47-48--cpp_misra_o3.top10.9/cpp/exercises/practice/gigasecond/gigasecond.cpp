#include "gigasecond.h"

namespace gigasecond {

auto advance(const boost::posix_time::ptime& start) -> boost::posix_time::ptime
{
    /* One gigasecond equals 1 000 000 000 s. */
    return (start + boost::posix_time::seconds{1000000000});
}

}  // namespace gigasecond
