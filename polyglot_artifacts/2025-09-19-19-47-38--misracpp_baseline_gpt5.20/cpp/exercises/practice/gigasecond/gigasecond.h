#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time_types.hpp>

namespace gigasecond {

boost::posix_time::ptime advance(const boost::posix_time::ptime& pt);

}  // namespace gigasecond

#endif // GIGASECOND_H
