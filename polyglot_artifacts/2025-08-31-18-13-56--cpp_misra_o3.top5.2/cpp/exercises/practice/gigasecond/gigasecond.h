#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <chrono>

namespace gigasecond {

auto advance(const std::chrono::system_clock::time_point& start) -> std::chrono::system_clock::time_point;

}  // namespace gigasecond

#endif // GIGASECOND_H
