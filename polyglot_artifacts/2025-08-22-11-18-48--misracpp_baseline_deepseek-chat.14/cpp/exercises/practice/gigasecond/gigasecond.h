#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

// Function to add a gigasecond to the given time
boost::posix_time::ptime advance(boost::posix_time::ptime start_time);

}  // namespace gigasecond

#endif // GIGASECOND_H
