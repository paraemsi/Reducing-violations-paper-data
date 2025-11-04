#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <chrono>

namespace gigasecond {

typedef std::chrono::system_clock::time_point time_point;

// For test compatibility, provide the expected function name 'advance'
time_point advance(const time_point& start);

}  // namespace gigasecond

#endif // GIGASECOND_H
