#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

typedef boost::posix_time::ptime ptime;
ptime advance(ptime tp);

}  // namespace gigasecond

#endif // GIGASECOND_H
