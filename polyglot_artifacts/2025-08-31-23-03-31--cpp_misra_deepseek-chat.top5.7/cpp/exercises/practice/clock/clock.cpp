#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(std::int32_t minutes) : total_minutes(minutes) {
}

clock clock::at(std::int32_t hours, std::int32_t minutes) {
    // Convert everything to total minutes
    std::int32_t total_minutes_from_input = (hours * 60) + minutes;
    // Normalize to be within 0-1439
    // Use modulo to handle large values, and adjust for negative
    total_minutes_from_input %= 1440;
    if (total_minutes_from_input < 0) {
        total_minutes_from_input += 1440;
    }
    return clock(total_minutes_from_input);
}

clock clock::plus(std::int32_t minutes) const {
    // Use 64-bit integers to prevent overflow during addition
    std::int64_t new_total = static_cast<std::int64_t>(total_minutes) + minutes;
    new_total %= 1440;
    if (new_total < 0) {
        new_total += 1440;
    }
    // new_total is between 0-1439, which fits in int32_t
    return clock(static_cast<std::int32_t>(new_total));
}

clock clock::minus(std::int32_t minutes) const {
    // Reuse plus by negating the minutes to subtract
    return plus(-minutes);
}

clock::operator std::string() const {
    // total_minutes is always between 0-1439
    std::int32_t hours = total_minutes / 60;
    std::int32_t mins = total_minutes % 60;
    // Since total_minutes is always positive, hours will be between 0-23
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours << ":"
        << std::setw(2) << std::setfill('0') << mins;
    return oss.str();
}

bool clock::operator==(const clock& other) const {
    return (total_minutes == other.total_minutes);
}

bool clock::operator!=(const clock& other) const {
    return (total_minutes != other.total_minutes);
}

}  // namespace date_independent
