#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <cstdint>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

using time_point_sec = boost::posix_time::ptime;

auto advance(const time_point_sec& start) -> time_point_sec;

}  // namespace gigasecond

#endif // GIGASECOND_H
