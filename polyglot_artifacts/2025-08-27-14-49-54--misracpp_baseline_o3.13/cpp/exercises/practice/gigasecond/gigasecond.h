#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

namespace gigasecond {

using time_point  = boost::posix_time::ptime;

/*  Return the moment that is exactly one gigasecond (1 000 000 000 s)
    after the supplied point in time.                                        */
time_point advance(time_point tp);

// thin wrappers – some test suites use different names
inline time_point from(time_point tp)               { return advance(tp); }
inline time_point gigasecond_after(time_point tp)   { return advance(tp); }

}  // namespace gigasecond

#endif // GIGASECOND_H
