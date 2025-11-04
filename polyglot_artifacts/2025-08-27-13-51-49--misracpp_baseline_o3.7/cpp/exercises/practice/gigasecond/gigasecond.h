#if !defined(GIGASECOND_H)
#define GIGASECOND_H
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

extern const boost::posix_time::seconds gigasecond_duration;

boost::posix_time::ptime advance(const boost::posix_time::ptime& tp);

}  // namespace gigasecond

#endif // GIGASECOND_H
