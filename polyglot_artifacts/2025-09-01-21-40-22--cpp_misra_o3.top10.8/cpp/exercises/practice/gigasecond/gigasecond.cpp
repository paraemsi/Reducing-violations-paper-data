#include "gigasecond.h"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

auto advance(const boost_ptime& start) -> boost_ptime
{
    const boost::posix_time::seconds one_gigasecond{1000000000};
    return start + one_gigasecond;
}

}  // namespace gigasecond
