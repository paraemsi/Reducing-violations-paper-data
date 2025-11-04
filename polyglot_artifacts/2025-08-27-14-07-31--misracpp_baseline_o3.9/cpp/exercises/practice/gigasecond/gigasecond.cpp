#include "gigasecond.h"
#include <chrono>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

constexpr std::chrono::seconds gigasecond_duration{1'000'000'000};


boost::posix_time::ptime advance(const boost::posix_time::ptime& pt) {
    return pt + boost::posix_time::seconds(
                     static_cast<long>(gigasecond_duration.count()));
}


}  // namespace gigasecond
