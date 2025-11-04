#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

static const boost::posix_time::time_duration gigasecond_duration =
    boost::posix_time::seconds(1000000000);

boost::posix_time::ptime advance(
    boost::posix_time::ptime const& start_time)
{
    return start_time + gigasecond_duration;
}

}  // namespace gigasecond
