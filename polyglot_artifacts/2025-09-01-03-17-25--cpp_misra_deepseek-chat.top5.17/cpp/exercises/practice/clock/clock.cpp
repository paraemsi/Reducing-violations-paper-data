#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {
    clock::clock(std::int32_t minutes) : minutes_since_midnight(minutes) {
        // Normalize to be within 0-1439
        // Handle negative values by adding enough days to make it positive
        if (minutes_since_midnight < 0) {
            // Add enough days to make it positive
            std::int32_t const days_to_add = static_cast<std::int32_t>(((-minutes_since_midnight) / 1440) + 1);
            minutes_since_midnight = static_cast<std::int32_t>(minutes_since_midnight + (days_to_add * 1440));
        }
        minutes_since_midnight %= 1440;
    }
    
    clock clock::at(std::int32_t hours, std::int32_t minutes) {
        // Convert hours and minutes to total minutes, which can be negative
        std::int32_t const total_minutes = static_cast<std::int32_t>((hours * 60) + minutes);
        return clock(total_minutes);
    }
    
    clock clock::plus(std::int32_t minutes_to_add) const {
        return clock(static_cast<std::int32_t>(minutes_since_midnight + minutes_to_add));
    }
    
    clock clock::minus(std::int32_t minutes_to_subtract) const {
        return clock(static_cast<std::int32_t>(minutes_since_midnight - minutes_to_subtract));
    }
    
    clock::operator std::string() const {
        // Since minutes_since_midnight is always between 0-1439, hours and minutes will be valid
        std::int32_t hours = static_cast<std::int32_t>(minutes_since_midnight / 60);
        std::int32_t minutes = static_cast<std::int32_t>(minutes_since_midnight % 60);
        
        // Ensure hours is within 0-23 (always true due to normalization)
        // But let's be safe
        hours %= 24;
        if (hours < 0) {
            hours += 24;
        }
        
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << hours << ":"
            << std::setw(2) << std::setfill('0') << minutes;
        return oss.str();
    }
    
    bool clock::operator==(const clock& other) const {
        return (minutes_since_midnight == other.minutes_since_midnight);
    }
    
    bool clock::operator!=(const clock& other) const {
        return (minutes_since_midnight != other.minutes_since_midnight);
    }
}  // namespace date_independent
