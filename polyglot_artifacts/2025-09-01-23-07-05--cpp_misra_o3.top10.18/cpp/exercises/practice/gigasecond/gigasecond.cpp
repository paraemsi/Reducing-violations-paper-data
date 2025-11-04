#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

    // 1 000 000 000 seconds expressed as a Boost posix_time duration.
    static const boost::posix_time::seconds gigasecond_duration(1000000000);

    boost::posix_time::ptime
    advance(const boost::posix_time::ptime& start)
    {
        return start + gigasecond_duration;
    }

}  // namespace gigasecond
