#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {
    clock::clock(std::int32_t minutes) : minutes_since_midnight(minutes) {}
    
    clock clock::at(std::int32_t hours, std::int32_t minutes) {
        // Calculate total minutes
        std::int32_t total_minutes = (hours * 60) + minutes;
        // Normalize to be within 0-1439
        total_minutes %= 1440;
        if (total_minutes < 0) {
            total_minutes += 1440;
        }
        return clock(total_minutes);
    }
    
    clock clock::plus(std::int32_t minutes_to_add) const {
        // Add minutes and normalize
        return clock::at(0, minutes_since_midnight + minutes_to_add);
    }
    
    clock clock::minus(std::int32_t minutes_to_subtract) const {
        // Subtract minutes and normalize
        return clock::at(0, minutes_since_midnight - minutes_to_subtract);
    }
    
    clock::operator std::string() const {
        // Since minutes_since_midnight is always between 0-1439, we can safely compute hours and minutes
        std::int32_t hours = minutes_since_midnight / 60;
        std::int32_t minutes = minutes_since_midnight % 60;
        
        // Format to HH:MM
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << hours << ":"
            << std::setw(2) << std::setfill('0') << minutes;
        return oss.str();
    }
    
    bool clock::operator==(const clock& other) const {
        return minutes_since_midnight == other.minutes_since_midnight;
    }
    
    bool clock::operator!=(const clock& other) const {
        return minutes_since_midnight != other.minutes_since_midnight;
    }
}  // namespace date_independent
