#if !defined(GIGASECOND_H)
#define GIGASECOND_H
#include <chrono>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

const boost::posix_time::seconds gigasecond_span{1'000'000'000};

boost::posix_time::ptime advance(const boost::posix_time::ptime& tp);

}  // namespace gigasecond

#endif // GIGASECOND_H
