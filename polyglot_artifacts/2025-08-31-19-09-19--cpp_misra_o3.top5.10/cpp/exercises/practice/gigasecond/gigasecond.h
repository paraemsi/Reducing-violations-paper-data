#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

/**
 * @brief Adds one gigasecond (1 000 000 000 seconds) to the supplied time point.
 *
 * @param tp A boost::posix_time::ptime representing the starting instant.
 * @return boost::posix_time::ptime The time point that is one gigasecond after tp.
 */
boost::posix_time::ptime advance(const boost::posix_time::ptime & tp);

}  // namespace gigasecond

#endif // GIGASECOND_H
