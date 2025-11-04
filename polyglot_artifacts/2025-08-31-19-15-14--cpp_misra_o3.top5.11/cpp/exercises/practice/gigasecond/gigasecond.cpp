#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace
{
/*  Constant duration representing exactly one gigasecond. */
const boost::posix_time::seconds gigasecond_duration{1'000'000'000};
}  // unnamed namespace

namespace gigasecond {

auto advance(const time_point& start) -> time_point
{
    return start + gigasecond_duration;
}

}  // namespace gigasecond
