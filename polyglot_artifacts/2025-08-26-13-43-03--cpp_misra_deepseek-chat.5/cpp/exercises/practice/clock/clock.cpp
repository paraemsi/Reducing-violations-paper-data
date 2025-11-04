#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(std::int32_t minutes) : minutes((minutes % 1440 + 1440) % 1440) {}

clock clock::at(std::int32_t hours, std::int32_t minutes) {
    // Convert everything to total minutes and normalize
    std::int32_t total_minutes = (hours * 60) + minutes;
    // Normalize to be within 0-1439
    total_minutes %= 1440;
    if (total_minutes < 0) {
        total_minutes += 1440;
    }
    return clock(total_minutes);
}

clock clock::plus(std::int32_t minutes_to_add) const {
    // Add minutes and normalize
    std::int32_t new_minutes = (minutes + minutes_to_add) % 1440;
    if (new_minutes < 0) {
        new_minutes += 1440;
    }
    return clock(new_minutes);
}

clock clock::minus(std::int32_t minutes_to_subtract) const {
    // Subtract by adding the negative
    return plus(-minutes_to_subtract);
}

clock::operator std::string() const {
    std::int32_t hrs = minutes / 60;
    std::int32_t mins = minutes % 60;
    // Handle the case where hours might be 24 (but it shouldn't be due to normalization)
    // Since minutes is always between 0-1439, hrs will be between 0-23
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
