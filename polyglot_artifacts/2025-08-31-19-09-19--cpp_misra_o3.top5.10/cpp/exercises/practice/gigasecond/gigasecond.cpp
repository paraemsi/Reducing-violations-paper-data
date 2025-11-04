#include "gigasecond.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime & tp)
{
    /* 1 000 000 000 seconds = 1 gigasecond */
    constexpr std::int64_t giga_second_value {1000000000};

    /* boost::posix_time::seconds expects a signed integral count
       (typically long on GNU/Linux).  The explicit cast is required
       and is a widening conversion on all mainstream 64-bit POSIX
       targets because both types are signed and have the same width. */
    return tp + boost::posix_time::seconds(
                   static_cast<boost::posix_time::time_duration::sec_type>(giga_second_value));
}

}  // namespace gigasecond
