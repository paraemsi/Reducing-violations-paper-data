#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

boost::posix_time::ptime advance(boost::posix_time::ptime time);

}  // namespace gigasecond

#endif // GIGASECOND_H
