#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(std::int32_t total_minutes) {
    // Normalize to be within 0-1439
    // Use 64-bit to handle large values
    std::int64_t normalized = total_minutes % 1440;
    if (normalized < 0) {
        normalized += 1440;
    }
    minutes = static_cast<std::int32_t>(normalized);
}

clock clock::at(std::int32_t hours, std::int32_t minutes) {
    // Use 64-bit to prevent overflow
    std::int64_t total_minutes = (static_cast<std::int64_t>(hours) * 60) + minutes;
    return clock(static_cast<std::int32_t>(total_minutes));
}

clock clock::plus(std::int32_t add_minutes) const {
    // Use 64-bit to prevent overflow
    std::int64_t new_minutes = (static_cast<std::int64_t>(minutes) + add_minutes) % 1440;
    if (new_minutes < 0) {
        new_minutes += 1440;
    }
    return clock(static_cast<std::int32_t>(new_minutes));
}

clock clock::minus(std::int32_t sub_minutes) const {
    return plus(-sub_minutes);
}

clock::operator std::string() const {
    std::int32_t hrs = minutes / 60;
    std::int32_t mins = minutes % 60;
    
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hrs << ":"
        << std::setw(2) << std::setfill('0') << mins;
    return oss.str();
}

bool clock::operator==(const clock& other) const {
    return minutes == other.minutes;
}

bool clock::operator!=(const clock& other) const {
    return !(*this == other);
}

}  // namespace date_independent
