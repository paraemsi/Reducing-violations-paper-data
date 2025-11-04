#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

inline boost::posix_time::ptime advance(boost::posix_time::ptime start_date) {
    return start_date + boost::posix_time::seconds(1000000000);
}

}  // namespace gigasecond

#endif // GIGASECOND_H
