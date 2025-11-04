#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(minute_t minutes) : minutes_((((minutes % 1440) + 1440) % 1440)) {
}

clock clock::at(int hours, int minutes) {
    // Cast to minute_t to ensure proper type handling
    minute_t cast_hours = static_cast<minute_t>(hours);
    minute_t cast_minutes = static_cast<minute_t>(minutes);
    minute_t total_minutes = (cast_hours * static_cast<minute_t>(60)) + cast_minutes;
    // Normalize to be within 0-1439 (number of minutes in a day)
    total_minutes = (total_minutes % static_cast<minute_t>(1440));
    if (total_minutes < static_cast<minute_t>(0)) {
        total_minutes = (total_minutes + static_cast<minute_t>(1440));
    }
    return clock(total_minutes);
}

clock clock::plus(int minutes) const {
    // Cast to minute_t to ensure proper type handling
    minute_t cast_minutes = static_cast<minute_t>(minutes);
    return clock((minutes_ + cast_minutes));
}

clock clock::minus(int minutes) const {
    // Cast to minute_t to ensure proper type handling
    minute_t cast_minutes = static_cast<minute_t>(minutes);
    return clock((minutes_ - cast_minutes));
}

clock::operator std::string() const {
    minute_t hours = (minutes_ / static_cast<minute_t>(60));
    minute_t minutes = (minutes_ % static_cast<minute_t>(60));
    
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours << ":" 
        << std::setw(2) << std::setfill('0') << minutes;
    return oss.str();
}

bool clock::operator==(const clock& other) const {
    return (minutes_ == other.minutes_);
}

bool clock::operator!=(const clock& other) const {
    return (minutes_ != other.minutes_);
}

}  // namespace date_independent
