#include "gigasecond.h"

namespace gigasecond {

namespace {
const boost::posix_time::seconds gigasecond_duration{1000000000};
}  // namespace

boost::posix_time::ptime advance(boost::posix_time::ptime start)
{
    return (start + gigasecond_duration);
}

}  // namespace gigasecond
