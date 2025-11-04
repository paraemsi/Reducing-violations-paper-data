#include "gigasecond.h"

#include <chrono>

namespace gigasecond {

constexpr auto gigasecond{std::chrono::seconds{1000000000}};

auto advance(const std::chrono::system_clock::time_point& start) -> std::chrono::system_clock::time_point
{
    return (start + gigasecond);
}

}  // namespace gigasecond
