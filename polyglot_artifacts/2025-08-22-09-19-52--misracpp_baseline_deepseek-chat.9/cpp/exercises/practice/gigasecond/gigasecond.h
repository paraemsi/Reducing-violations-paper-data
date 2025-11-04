#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

inline boost::posix_time::ptime advance(const boost::posix_time::ptime& start) {
    return start + boost::posix_time::seconds(1000000000);
}

}  // namespace gigasecond

#endif // GIGASECOND_H
