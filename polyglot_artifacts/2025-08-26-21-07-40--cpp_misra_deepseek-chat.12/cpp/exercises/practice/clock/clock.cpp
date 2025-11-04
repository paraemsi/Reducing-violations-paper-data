#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {
    clock::clock(std::int32_t total_minutes) {
        // Normalize to be within 0-1439
        // Handle negative values by adding enough days to make it positive
        if (total_minutes < 0) {
            total_minutes %= 1440;
            total_minutes += 1440;
        }
        // Handle positive values
        minutes = total_minutes % 1440;
        // Ensure it's positive (modulo of negative numbers can be tricky)
        if (minutes < 0) {
            minutes += 1440;
        }
    }

    clock clock::at(std::int32_t hours, std::int32_t minutes) {
        // Convert hours to minutes and add
        std::int32_t total_minutes = (hours * 60) + minutes;
        return clock(total_minutes);
    }

    clock clock::plus(std::int32_t minutes_to_add) const {
        // Add minutes and normalize
        std::int32_t new_minutes = minutes + minutes_to_add;
        return clock(new_minutes);
    }

    clock clock::minus(std::int32_t minutes_to_subtract) const {
        // Subtract minutes by adding negative
        return this->plus(-minutes_to_subtract);
    }

    clock::operator std::string() const {
        std::int32_t hours = minutes / 60;
        std::int32_t mins = minutes % 60;
        // Handle hours that might be 24 or more (but they shouldn't be due to normalization)
        hours %= 24;
        
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << hours << ":"
            << std::setw(2) << std::setfill('0') << mins;
        return oss.str();
    }

    bool clock::operator==(const clock& other) const {
        return minutes == other.minutes;
    }

    bool clock::operator!=(const clock& other) const {
        return !(*this == other);
    }
}  // namespace date_independent
