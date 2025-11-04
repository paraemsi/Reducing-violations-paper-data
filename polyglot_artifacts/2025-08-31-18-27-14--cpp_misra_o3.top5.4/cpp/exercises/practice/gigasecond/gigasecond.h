#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <chrono>
#include <cstdint>

namespace gigasecond {

/*  Advance the supplied time point by one gigasecond (1 000 000 000 s).  */
auto advance(const std::chrono::system_clock::time_point& start)
    -> std::chrono::system_clock::time_point;

}  // namespace gigasecond

#endif // GIGASECOND_H
