#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

#ifndef GIGASECOND_NODISCARD
#  if defined(__has_cpp_attribute)
#    if __has_cpp_attribute(nodiscard)
#      define GIGASECOND_NODISCARD [[nodiscard]]
#    else
#      define GIGASECOND_NODISCARD
#    endif
#  else
#    define GIGASECOND_NODISCARD
#  endif
#endif

namespace gigasecond {

using time_point = boost::posix_time::ptime;

GIGASECOND_NODISCARD time_point add(const time_point& tp) noexcept;
GIGASECOND_NODISCARD time_point advance(const time_point& tp) noexcept;

}  // namespace gigasecond

#endif // GIGASECOND_H
