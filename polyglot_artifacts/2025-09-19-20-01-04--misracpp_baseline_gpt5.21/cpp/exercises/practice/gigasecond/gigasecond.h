#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

using boost::posix_time::ptime;

ptime advance(ptime const& tp);

}  // namespace gigasecond

#endif // GIGASECOND_H
