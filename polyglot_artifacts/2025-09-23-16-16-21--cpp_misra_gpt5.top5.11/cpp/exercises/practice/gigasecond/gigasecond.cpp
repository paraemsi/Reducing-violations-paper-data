#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

auto advance(boost::posix_time::ptime const& t) -> boost::posix_time::ptime
{
    static constexpr std::int64_t giga{static_cast<std::int64_t>(1000000000)};
    return (t + boost::posix_time::seconds(static_cast<boost::posix_time::time_duration::sec_type>(giga)));
}

}  // namespace gigasecond
