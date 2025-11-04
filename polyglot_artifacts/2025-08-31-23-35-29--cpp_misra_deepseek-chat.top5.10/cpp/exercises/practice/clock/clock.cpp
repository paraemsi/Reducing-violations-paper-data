#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(std::int32_t total_minutes) 
    : total_minutes_((total_minutes % 1440 + 1440) % 1440) {
}

clock clock::at(std::int32_t hours, std::int32_t minutes) {
    // Convert hours and minutes to total minutes
    // Handle potential overflow by using modulo arithmetic
    std::int32_t total_minutes = (hours * 60) + minutes;
    // Normalize to be within 0-1439
    total_minutes %= 1440;
    if (total_minutes < 0) {
        total_minutes += 1440;
    }
    return clock(total_minutes);
}

clock clock::plus(std::int32_t minutes) const {
    return clock(total_minutes_ + minutes);
}

clock clock::minus(std::int32_t minutes) const {
    return clock(total_minutes_ - minutes);
}

clock::operator std::string() const {
    // total_minutes_ is always between 0-1439
    std::int32_t hours = total_minutes_ / 60;
    std::int32_t minutes = total_minutes_ % 60;
    
    // Format to HH:MM
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours << ":"
        << std::setw(2) << std::setfill('0') << minutes;
    return oss.str();
}

bool clock::operator==(const clock& other) const {
    return (total_minutes_ == other.total_minutes_);
}

bool clock::operator!=(const clock& other) const {
    return (total_minutes_ != other.total_minutes_);
}

}  // namespace date_independent
