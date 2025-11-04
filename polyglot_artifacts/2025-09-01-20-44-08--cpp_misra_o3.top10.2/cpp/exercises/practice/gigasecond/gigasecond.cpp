#include "gigasecond.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

namespace
{
    // One gigasecond expressed as a 64-bit signed constant
    static constexpr std::int64_t GIGASECOND{1000000000};
} // unnamed namespace

auto advance(const time_point& start) -> time_point
{
    // Construct a duration explicitly from the constant to avoid implicit conversions
    const auto delta{boost::posix_time::seconds{GIGASECOND}};
    return start + delta;
}

}  // namespace gigasecond
