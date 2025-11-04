#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(std::int32_t minutes) 
    : total_minutes((minutes % 1440 + 1440) % 1440) {
}

clock clock::at(std::int32_t hours, std::int32_t minutes) {
    std::int32_t total_minutes_from_input = (hours * 60) + minutes;
    // Normalize to be within 0-1439
    std::int32_t normalized_minutes = total_minutes_from_input % 1440;
    if (normalized_minutes < 0) {
        normalized_minutes += 1440;
    }
    return clock(normalized_minutes);
}

clock clock::plus(std::int32_t minutes_to_add) const {
    std::int32_t new_minutes = total_minutes + minutes_to_add;
    // Normalize to be within 0-1439
    std::int32_t normalized_minutes = new_minutes % 1440;
    if (normalized_minutes < 0) {
        normalized_minutes += 1440;
    }
    return clock(normalized_minutes);
}

clock clock::minus(std::int32_t minutes_to_subtract) const {
    std::int32_t new_minutes = total_minutes - minutes_to_subtract;
    // Normalize to be within 0-1439
    std::int32_t normalized_minutes = new_minutes % 1440;
    if (normalized_minutes < 0) {
        normalized_minutes += 1440;
    }
    return clock(normalized_minutes);
}

clock::operator std::string() const {
    std::int32_t hours = total_minutes / 60;
    std::int32_t minutes = total_minutes % 60;
    
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
