#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

boost::posix_time::ptime advance(boost::posix_time::ptime tp)
{
    // Add one gigasecond (1_000_000_000 seconds) to the provided time point.
    static const boost::posix_time::seconds one_gigasecond(1000000000);
    return (tp + one_gigasecond);
}

}  // namespace gigasecond
