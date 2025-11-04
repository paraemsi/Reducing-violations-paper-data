#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(std::int32_t total_minutes) {
    // Normalize to be within 0-1439
    // Handle negative values by adding enough days to make it positive first
    total_minutes %= 1440;
    if (total_minutes < 0) {
        total_minutes += 1440;
    }
    minutes = total_minutes;
}

clock clock::at(int hours, int minutes) {
    // Calculate total minutes, which can be negative or very large
    std::int32_t total_minutes = (static_cast<std::int32_t>(hours) * 60) + static_cast<std::int32_t>(minutes);
    return clock(total_minutes);
}

clock clock::plus(int add_minutes) const {
    // Add minutes and normalize
    return clock(minutes + static_cast<std::int32_t>(add_minutes));
}

clock clock::minus(int sub_minutes) const {
    // Subtract minutes and normalize
    return clock(minutes - static_cast<std::int32_t>(sub_minutes));
}

clock::operator std::string() const {
    // Get hours and minutes
    std::int32_t hrs = minutes / 60;
    std::int32_t mins = minutes % 60;
    
    // Format to HH:MM
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hrs << ":"
        << std::setfill('0') << std::setw(2) << mins;
    return oss.str();
}

bool clock::operator==(const clock& other) const {
    return minutes == other.minutes;
}

bool clock::operator!=(const clock& other) const {
    return minutes != other.minutes;
}

}  // namespace date_independent
