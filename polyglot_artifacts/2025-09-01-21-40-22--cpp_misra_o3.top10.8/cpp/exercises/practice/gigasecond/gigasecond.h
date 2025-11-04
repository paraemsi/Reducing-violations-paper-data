#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

using boost_ptime = boost::posix_time::ptime;

[[nodiscard]] auto advance(const boost_ptime& start) -> boost_ptime;

}  // namespace gigasecond

#endif // GIGASECOND_H
