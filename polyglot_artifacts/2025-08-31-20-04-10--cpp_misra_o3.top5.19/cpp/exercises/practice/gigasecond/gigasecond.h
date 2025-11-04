#if !defined(GIGASECOND_H)
#define GIGASECOND_H
#include <cstdint>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

using ptime = boost::posix_time::ptime;

[[nodiscard]] auto advance(const ptime &moment) -> ptime;

}  // namespace gigasecond

#endif // GIGASECOND_H
