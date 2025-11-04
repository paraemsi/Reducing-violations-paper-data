#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

time_point advance(time_point tp) {
    // add one gigasecond (1 000 000 000 seconds)
    return tp + boost::posix_time::seconds(1000000000);
}

}  // namespace gigasecond
