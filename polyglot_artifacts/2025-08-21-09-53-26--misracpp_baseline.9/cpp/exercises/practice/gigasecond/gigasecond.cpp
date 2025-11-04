#include "gigasecond.h"

namespace gigasecond {

std::chrono::system_clock::time_point advance(const std::chrono::system_clock::time_point& start) {
    // 1 gigasecond = 1,000,000,000 seconds
    return start + std::chrono::seconds(1000000000);
}

}  // namespace gigasecond
