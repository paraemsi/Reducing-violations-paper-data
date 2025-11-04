#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

/* Returns the moment one gigasecond after the given time point. */
boost::posix_time::ptime advance(boost::posix_time::ptime tp);

}  // namespace gigasecond

#endif // GIGASECOND_H
