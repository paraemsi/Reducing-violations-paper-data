#include "gigasecond.h"

namespace gigasecond {

namespace
{
    // One gigasecond expressed as a boost::posix_time::seconds duration.
    const boost::posix_time::time_duration gigasecond_duration =
        boost::posix_time::seconds(static_cast<std::int64_t>(1000000000));
} // anonymous namespace

boost::posix_time::ptime advance(const boost::posix_time::ptime& start) noexcept
{
    return start + gigasecond_duration;
}

}  // namespace gigasecond
