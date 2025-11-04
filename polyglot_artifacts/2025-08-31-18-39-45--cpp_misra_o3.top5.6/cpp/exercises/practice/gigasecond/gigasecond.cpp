#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

static const boost::posix_time::seconds gigasecond_duration(1000000000);

auto advance(const boost::posix_time::ptime& start)
    -> boost::posix_time::ptime
{
    return start + gigasecond_duration;
}

}  // namespace gigasecond
