#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

using time_point = boost::posix_time::ptime;

// Return the time that is exactly one gigasecond (1 000 000 000 s) after `t`.
time_point advance(time_point t);

}  // namespace gigasecond

#endif // GIGASECOND_H
