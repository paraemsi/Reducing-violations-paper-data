#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(std::int32_t total_minutes) 
    : total_minutes_(total_minutes) {
}

clock clock::at(std::int32_t hours, std::int32_t minutes) {
    // Convert everything to total minutes first
    std::int32_t total_minutes = (hours * 60) + minutes;
    // Normalize to be within 0-1439
    total_minutes %= 1440;
    if (total_minutes < 0) {
        total_minutes += 1440;
    }
    return clock(total_minutes);
}

clock clock::plus(std::int32_t minutes) const {
    // Add minutes and normalize
    std::int32_t new_total_minutes = (total_minutes_ + minutes) % 1440;
    if (new_total_minutes < 0) {
        new_total_minutes += 1440;
    }
    return clock(new_total_minutes);
}

clock clock::minus(std::int32_t minutes) const {
    // Subtract minutes by adding negative
    return plus(-minutes);
}

clock::operator std::string() const {
    // Since total_minutes_ is always between 0 and 1439, we can safely compute hours and minutes
    std::int32_t hours = total_minutes_ / 60;
    std::int32_t minutes = total_minutes_ % 60;
    
    // Format the string
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours << ":"
        << std::setw(2) << std::setfill('0') << minutes;
    return oss.str();
}

bool clock::operator==(const clock& other) const {
    return total_minutes_ == other.total_minutes_;
}

bool clock::operator!=(const clock& other) const {
    return total_minutes_ != other.total_minutes_;
}

}  // namespace date_independent
