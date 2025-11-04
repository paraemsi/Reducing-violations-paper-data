#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(std::int32_t total_minutes) {
    // Normalize to be within 0-1439 minutes (24 hours)
    // Handle negative values by adding enough days to make it positive
    std::int32_t normalized_minutes = total_minutes % 1440;
    if (normalized_minutes < 0) {
        normalized_minutes += 1440;
    }
    minutes = normalized_minutes;
}

clock clock::at(std::int32_t hours, std::int32_t minutes_val) {
    // Convert everything to total minutes first, then normalize
    std::int32_t total_minutes = (hours * 60) + minutes_val;
    // Normalize to be within 0-1439 minutes (24 hours)
    // Handle negative values by adding enough days to make it positive
    std::int32_t normalized_minutes = total_minutes % 1440;
    if (normalized_minutes < 0) {
        normalized_minutes += 1440;
    }
    return clock(normalized_minutes);
}

clock clock::plus(std::int32_t minutes_to_add) const {
    return clock(minutes + minutes_to_add);
}

clock clock::minus(std::int32_t minutes_to_subtract) const {
    return clock(minutes - minutes_to_subtract);
}

clock::operator std::string() const {
    // Since minutes is always between 0-1439, hours will be between 0-23
    std::int32_t hrs = minutes / 60;
    std::int32_t mins = minutes % 60;
    // Make sure to take modulo 24 for hours to handle cases where hrs could be 24
    // But since minutes is always < 1440, hrs will always be < 24
    hrs %= 24;
    
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
