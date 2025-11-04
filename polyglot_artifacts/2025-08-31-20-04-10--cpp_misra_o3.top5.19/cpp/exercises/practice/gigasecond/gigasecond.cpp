#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

constexpr std::int64_t gigasecond_count{static_cast<std::int64_t>(1'000'000'000)};

auto advance(const ptime &moment) -> ptime
{
    /* boost::posix_time::seconds constructor takes a signed long; an explicit
     * cast avoids any implicit conversion warnings and complies with MISRA
     * “assignment between numeric types shall be appropriate”. */
    return (moment + boost::posix_time::seconds{static_cast<long>(gigasecond_count)});
}

}  // namespace gigasecond
