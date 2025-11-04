#include "gigasecond.h"

namespace gigasecond {

const long long GIGASECOND = 1000000000;

std::chrono::system_clock::time_point advance(const std::chrono::system_clock::time_point& start) {
    return start + std::chrono::seconds(GIGASECOND);
}

}  // namespace gigasecond
