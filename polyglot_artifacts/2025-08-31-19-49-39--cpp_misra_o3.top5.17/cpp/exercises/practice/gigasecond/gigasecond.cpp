#include "gigasecond.h"

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

auto advance(const boost::posix_time::ptime& start) -> boost::posix_time::ptime
{
    const auto gigasec{ boost::posix_time::seconds(1'000'000'000) };
    return start + gigasec;
}

}  // namespace gigasecond
