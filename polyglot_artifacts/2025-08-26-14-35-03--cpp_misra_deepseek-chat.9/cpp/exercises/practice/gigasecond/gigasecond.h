#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

inline boost::posix_time::ptime advance(const boost::posix_time::ptime& start) {
    constexpr std::int64_t gigasecond = 1000000000;
    return start + boost::posix_time::seconds(gigasecond);
}

}  // namespace gigasecond

#endif // GIGASECOND_H
