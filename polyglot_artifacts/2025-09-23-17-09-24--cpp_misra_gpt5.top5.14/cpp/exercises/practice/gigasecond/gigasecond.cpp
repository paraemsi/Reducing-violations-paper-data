#include "gigasecond.h"

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

namespace {
const boost::posix_time::time_duration one_gigasecond = boost::posix_time::seconds(1000000000);
}  // namespace

boost::posix_time::ptime advance(const boost::posix_time::ptime& tp) noexcept
{
    return (tp + one_gigasecond);
}

}  // namespace gigasecond
