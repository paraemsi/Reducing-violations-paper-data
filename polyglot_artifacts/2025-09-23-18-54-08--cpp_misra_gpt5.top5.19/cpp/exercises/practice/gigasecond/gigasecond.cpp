#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& tp)
{
    const auto one_gigasecond = boost::posix_time::seconds(1000000000);
    return (tp + one_gigasecond);
}

}  // namespace gigasecond
