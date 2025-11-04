#if !defined(GIGASECOND_H)
#define GIGASECOND_H

#include <chrono>

namespace gigasecond {

/*
 * Add exactly one gigasecond (1 000 000 000 s) to the supplied time-point.
 *
 * The interface expected by the Exercism tests is a non-templated
 * free function that operates on std::chrono::system_clock::time_point.
 */
[[nodiscard]] auto advance(
    const std::chrono::system_clock::time_point& start_time)
    -> std::chrono::system_clock::time_point;

}  // namespace gigasecond

#endif // GIGASECOND_H
