#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {


/* Calculate the moment that occurs exactly one gigasecond after the
 * provided time point.
 */
auto advance(boost::posix_time::ptime const& t) -> boost::posix_time::ptime;

}  // namespace gigasecond

#endif // GIGASECOND_H
