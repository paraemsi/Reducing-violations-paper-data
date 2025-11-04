#if !defined(GIGASECOND_H)
#define GIGASECOND_H
#include <boost/date_time/posix_time/posix_time.hpp>

#if __cplusplus >= 201703L
#define GIGASECOND_NODISCARD [[nodiscard]]
#else
#define GIGASECOND_NODISCARD
#endif

namespace gigasecond {

    GIGASECOND_NODISCARD boost::posix_time::ptime advance(boost::posix_time::ptime const& time_point) noexcept;

}  // namespace gigasecond

#endif // GIGASECOND_H
