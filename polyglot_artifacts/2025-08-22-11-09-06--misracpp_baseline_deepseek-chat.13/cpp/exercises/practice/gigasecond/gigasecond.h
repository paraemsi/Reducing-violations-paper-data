#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

// Add one gigasecond (1,000,000,000 seconds) to the given time
boost::posix_time::ptime advance(const boost::posix_time::ptime& start);

}  // namespace gigasecond

#endif // GIGASECOND_H
