#if !defined(GIGASECOND_H)
#define GIGASECOND_H
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

    // Return the instant that occurs exactly one gigasecond
    // (1 000 000 000 seconds) after the supplied time-point.
    //
    // A boost::posix_time::ptime is returned so callers may utilise
    // Boost.Date_Time utilities without any further conversion.
    boost::posix_time::ptime advance(
        boost::posix_time::ptime const& start_time);

}  // namespace gigasecond

#endif // GIGASECOND_H
