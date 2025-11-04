#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

using ptime = boost::posix_time::ptime;

auto advance(const ptime& start) -> ptime;

} // namespace gigasecond

#endif // GIGASECOND_H
