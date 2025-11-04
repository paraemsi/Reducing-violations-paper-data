#if !defined(GIGASECOND_H)
#define GIGASECOND_H
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cstdint>

#if (__cplusplus >= 201703L)
#define GIGASECOND_NODISCARD [[nodiscard]]
#else
#define GIGASECOND_NODISCARD
#endif

namespace gigasecond {

    // Adds one gigasecond (1 000 000 000 seconds) to the supplied
    // std::chrono::system_clock::time_point.
    //
    // The function adheres to MISRA C++ rules by avoiding implicit
    // conversions and using fixed-width integer types explicitly.
    GIGASECOND_NODISCARD boost::posix_time::ptime add(
        const boost::posix_time::ptime& start);

    // Back-compatibility wrapper expected by the test suite.
    GIGASECOND_NODISCARD boost::posix_time::ptime advance(
        const boost::posix_time::ptime& start);

}  // namespace gigasecond

#endif // GIGASECOND_H
