#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

namespace gigasecond {

// Constant gigasecond duration expressed in seconds.
// Use a plain literal to keep the definition simple and still satisfy the
// fixed-width requirement.
// Keep the literal type explicit to avoid any implicit integral promotions.
// A plain literal fits safely in 32 bits, so no cast is required.
constexpr std::int64_t gigasecond{1000000000};

// Return the time point that is exactly one gigasecond after the supplied start
// time.
boost::posix_time::ptime advance(const boost::posix_time::ptime& start) noexcept;

}  // namespace gigasecond

#endif // GIGASECOND_H
