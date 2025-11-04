#include "clock.h"
#include <cstdint>
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {

namespace clock {

Clock::Clock(std::int32_t hours, std::int32_t minutes) {
    // Convert hours and minutes to total minutes
    total_minutes_ = normalize((hours * 60) + minutes);
}

Clock Clock::plus(std::int32_t minutes) const {
    std::int32_t new_minutes = total_minutes_ + minutes;
    std::int32_t normalized = normalize(new_minutes);
    return Clock(0, normalized);
}

Clock Clock::minus(std::int32_t minutes) const {
    std::int32_t new_minutes = total_minutes_ - minutes;
    std::int32_t normalized = normalize(new_minutes);
    return Clock(0, normalized);
}

bool Clock::operator==(const Clock& other) const {
    return total_minutes_ == other.total_minutes_;
}

bool Clock::operator!=(const Clock& other) const {
    return !((*this) == other);
}

Clock::operator std::string() const {
    std::int32_t hours = total_minutes_ / 60;
    std::int32_t minutes = total_minutes_ % 60;
    
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hours 
        << ':' 
        << std::setfill('0') << std::setw(2) << minutes;
    return oss.str();
}

std::int32_t Clock::normalize(std::int32_t minutes) {
    // Handle negative minutes by adding full days until positive
    std::int32_t result = minutes;
    while (result < 0) {
        result = result + 1440; // 1440 minutes in a day
    }
    
    // Wrap around if we exceed 24 hours
    result = result % 1440;
    return result;
}

Clock at(std::int32_t hour, std::int32_t minute) {
    return Clock(hour, minute);
}

}  // namespace clock

}  // namespace date_independent
