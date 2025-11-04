#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <chrono>

namespace gigasecond {

using time_point = std::chrono::system_clock::time_point;

time_point advance(const time_point& start);

inline time_point add(const time_point& start) { return advance(start); }

}  // namespace gigasecond

#endif // GIGASECOND_H
