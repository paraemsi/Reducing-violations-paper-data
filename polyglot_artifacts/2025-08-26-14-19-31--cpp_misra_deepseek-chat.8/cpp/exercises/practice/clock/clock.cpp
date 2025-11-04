#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {
    clock::clock(std::int32_t total_minutes) {
        // Normalize to be within 0-1439
        // Handle negative values by adding enough days to make it positive
        std::int32_t normalized_minutes = total_minutes % 1440;
        if (normalized_minutes < 0) {
            normalized_minutes += 1440;
        }
        minutes = normalized_minutes;
    }

    clock clock::at(std::int32_t hours, std::int32_t minutes) {
        std::int32_t total_minutes = (hours * 60) + minutes;
        return clock(total_minutes);
    }

    clock clock::plus(std::int32_t minutes_to_add) const {
        return clock(minutes + minutes_to_add);
    }

    clock clock::minus(std::int32_t minutes_to_subtract) const {
        return clock(minutes - minutes_to_subtract);
    }

    clock::operator std::string() const {
        // Since minutes is always between 0-1439, hours will be between 0-23
        std::int32_t hours = minutes / 60;
        std::int32_t mins = minutes % 60;
        
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << hours << ":"
            << std::setw(2) << std::setfill('0') << mins;
        return oss.str();
    }

    bool clock::operator==(const clock& other) const {
        return minutes == other.minutes;
    }

    bool clock::operator!=(const clock& other) const {
        return minutes != other.minutes;
    }
}  // namespace date_independent
