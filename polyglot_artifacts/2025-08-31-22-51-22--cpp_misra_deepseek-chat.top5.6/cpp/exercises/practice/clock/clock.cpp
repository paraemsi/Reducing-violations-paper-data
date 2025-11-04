#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {
    clock::clock(std::int32_t minutes) : minutes_since_midnight(minutes) {
        // Ensure minutes are always within 0-1439
        minutes_since_midnight %= 1440;
        if (minutes_since_midnight < 0) {
            minutes_since_midnight += 1440;
        }
    }
    
    clock clock::at(std::int32_t hours, std::int32_t minutes) {
        // Convert hours and minutes to total minutes
        std::int32_t total_minutes = (hours * 60) + minutes;
        return clock(total_minutes);
    }
    
    clock clock::plus(std::int32_t minutes_to_add) const {
        std::int32_t new_minutes = minutes_since_midnight + minutes_to_add;
        return clock(new_minutes);
    }
    
    clock clock::minus(std::int32_t minutes_to_subtract) const {
        std::int32_t new_minutes = minutes_since_midnight - minutes_to_subtract;
        return clock(new_minutes);
    }
    
    clock::operator std::string() const {
        // Since minutes_since_midnight is always between 0 and 1439
        std::int32_t hours = minutes_since_midnight / 60;
        std::int32_t minutes = minutes_since_midnight % 60;
        
        // Adjust hours to be between 0 and 23 (always true due to our normalization)
        // But let's ensure it's within bounds
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
