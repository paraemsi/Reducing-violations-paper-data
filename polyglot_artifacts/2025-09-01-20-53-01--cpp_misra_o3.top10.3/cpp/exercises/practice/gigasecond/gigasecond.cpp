#include "gigasecond.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

namespace
{
    /* Duration of one gigasecond expressed in seconds */
    constexpr std::int64_t gigasecond_count{ static_cast<std::int64_t>(1000000000) };
} // unnamed namespace

auto advance(const boost::posix_time::ptime& start_time) -> boost::posix_time::ptime
{
    return start_time + boost::posix_time::seconds(
        static_cast<boost::posix_time::time_duration::sec_type>(gigasecond_count));
}

}  // namespace gigasecond
