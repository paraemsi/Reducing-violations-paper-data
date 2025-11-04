#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

const boost::posix_time::time_duration gigasecond_duration{
    boost::posix_time::seconds(static_cast<std::int64_t>(1'000'000'000))};

auto advance(const time_point_sec& start) -> time_point_sec
{
    return (start + gigasecond_duration);
}

}  // namespace gigasecond
