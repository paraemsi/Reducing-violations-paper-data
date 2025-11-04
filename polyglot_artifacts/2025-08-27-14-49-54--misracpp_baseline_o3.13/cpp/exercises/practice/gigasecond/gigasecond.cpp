#include "gigasecond.h"

namespace gigasecond {

constexpr boost::posix_time::seconds one_gigasecond{1'000'000'000};

time_point advance(time_point tp)
{
    return tp + one_gigasecond;
}

}  // namespace gigasecond
