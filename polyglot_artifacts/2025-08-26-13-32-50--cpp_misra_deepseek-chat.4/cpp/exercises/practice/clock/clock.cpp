#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {

std::int32_t clock::normalize(std::int32_t minutes) {
    // Normalize to be within [0, 1439]
    minutes %= 1440;
    if (minutes < 0) {
        minutes += 1440;
    }
    return minutes;
}

clock::clock(std::int32_t minutes) : total_minutes(normalize(minutes)) {}

clock clock::at(std::int32_t hours, std::int32_t minutes) {
    // Convert hours and minutes to total minutes using int64_t to prevent overflow
    std::int64_t total_minutes_from_input = (static_cast<std::int64_t>(hours) * 60) + minutes;
    return clock(static_cast<std::int32_t>(total_minutes_from_input));
}

clock clock::plus(std::int32_t minutes) const {
    return clock(total_minutes + minutes);
}

clock clock::minus(std::int32_t minutes) const {
    return clock(total_minutes - minutes);
}

clock::operator std::string() const {
    std::int32_t hours = total_minutes / 60;
    std::int32_t minutes = total_minutes % 60;
    
    // Since total_minutes is always normalized, hours will be between 0 and 23
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours << ":"
        << std::setw(2) << std::setfill('0') << minutes;
    return oss.str();
}

bool clock::operator==(const clock& other) const {
    return (total_minutes == other.total_minutes);
}

bool clock::operator!=(const clock& other) const {
    return (total_minutes != other.total_minutes);
}

}  // namespace date_independent
