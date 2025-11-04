#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

inline boost::posix_time::ptime advance(boost::posix_time::ptime start) {
    return start + boost::posix_time::seconds(1000000000LL);
}

}  // namespace gigasecond

#endif // GIGASECOND_H
