#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <boost/date_time/posix_time/posix_time.hpp>

#if __cplusplus >= 201703L
#define GIGASECOND_NODISCARD [[nodiscard]]
#else
#define GIGASECOND_NODISCARD
#endif

namespace gigasecond {

/*
 * @brief Calculate the time point that occurs exactly one gigasecond
 *        (1 000 000 000 seconds) after the supplied time point.
 *
 * @param[in]  tp  The starting point in time.
 * @return          A boost::posix_time::ptime that is
 *                  one gigasecond after tp.
 */
GIGASECOND_NODISCARD boost::posix_time::ptime advance(
    const boost::posix_time::ptime& tp) noexcept;

}  // namespace gigasecond

#endif // GIGASECOND_H
