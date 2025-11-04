#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

auto advance(boost::posix_time::ptime const& t) -> boost::posix_time::ptime;

}  // namespace gigasecond

#endif // GIGASECOND_H
