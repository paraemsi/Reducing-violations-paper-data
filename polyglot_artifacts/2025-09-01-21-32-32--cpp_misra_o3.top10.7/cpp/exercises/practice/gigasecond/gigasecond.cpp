#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

boost::posix_time::ptime advance(boost::posix_time::ptime start)
{
    /* Add exactly one gigasecond (1 000 000 000 s) to the input instant. */
    return (start + boost::posix_time::seconds{static_cast<long>(1000000000)});
}

}  // namespace gigasecond
