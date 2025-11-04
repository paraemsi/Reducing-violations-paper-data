#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

// Alias for integer type
using seconds_count_t = std::int64_t;

inline boost::posix_time::ptime advance(const boost::posix_time::ptime& start) {
    const seconds_count_t gigasecond_count = 1000000000;
    boost::posix_time::seconds gigasecond_duration(gigasecond_count);
    return start + gigasecond_duration;
}

}  // namespace gigasecond

#endif // GIGASECOND_H
