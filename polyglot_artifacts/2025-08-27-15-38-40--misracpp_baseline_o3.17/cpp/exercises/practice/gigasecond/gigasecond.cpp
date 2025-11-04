#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

ptime advance(const ptime& pt) {
    return pt + boost::posix_time::seconds(GIGASECOND);
}

}  // namespace gigasecond
