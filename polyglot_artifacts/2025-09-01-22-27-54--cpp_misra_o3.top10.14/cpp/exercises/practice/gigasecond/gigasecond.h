#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

using time_point = boost::posix_time::ptime;

auto advance(const time_point& start) noexcept -> time_point;

}  // namespace gigasecond

#endif // GIGASECOND_H
