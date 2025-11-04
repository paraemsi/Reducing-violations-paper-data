#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <cstdint>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

 // Duration representing exactly one gigasecond (1 000 000 000 seconds)
extern const ::boost::posix_time::time_duration gigasecond_duration;

auto advance(const ::boost::posix_time::ptime& start)
    -> ::boost::posix_time::ptime;

}  // namespace gigasecond

#endif // GIGASECOND_H
