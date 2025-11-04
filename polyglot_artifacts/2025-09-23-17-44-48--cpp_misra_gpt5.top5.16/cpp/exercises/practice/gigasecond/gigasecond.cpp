#include "gigasecond.h"

namespace gigasecond {

namespace {
const boost::posix_time::seconds one_gigasecond(1000000000);
}  // namespace

boost::posix_time::ptime advance(boost::posix_time::ptime tp)
{
    return (tp + one_gigasecond);
}

}  // namespace gigasecond
