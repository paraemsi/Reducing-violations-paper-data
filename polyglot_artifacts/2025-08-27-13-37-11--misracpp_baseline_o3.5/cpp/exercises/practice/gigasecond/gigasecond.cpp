#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& tp) {
    static const boost::posix_time::time_duration gigasecond =
        boost::posix_time::seconds(1'000'000'000);
    return tp + gigasecond;
}

}  // namespace gigasecond
