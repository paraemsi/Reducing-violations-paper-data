#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {
    clock::clock(std::int32_t minutes) : minutes(minutes) {}
    
    clock clock::at(std::int32_t hours, std::int32_t minutes) {
        // Calculate total minutes
        std::int32_t total_minutes = (hours * 60) + minutes;
        // Normalize to be within 0-1439
        // Handle negative values by adding enough days
        total_minutes %= 1440;
        if (total_minutes < 0) {
            total_minutes += 1440;
        }
        return clock(total_minutes);
    }
    
    clock clock::plus(std::int32_t minutes_to_add) const {
        // Add minutes and normalize
        std::int32_t new_minutes = (minutes + minutes_to_add) % 1440;
        if (new_minutes < 0) {
            new_minutes += 1440;
        }
        return clock(new_minutes);
    }
    
    clock clock::minus(std::int32_t minutes_to_subtract) const {
        // Subtract minutes and normalize
        // This is the same as adding negative minutes
        return plus(-minutes_to_subtract);
    }
    
    clock::operator std::string() const {
        // Since minutes is always between 0 and 1439, we can safely compute hours and minutes
        std::int32_t hours = minutes / 60;
        std::int32_t mins = minutes % 60;
        
        // Adjust hours to be within 0-23 (but due to normalization, it always will be)
        hours %= 24;
        if (hours < 0) {
            hours += 24;
        }
        
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << hours << ":"
            << std::setw(2) << std::setfill('0') << mins;
        return oss.str();
    }
    
    bool clock::operator==(const clock& other) const {
        return (minutes == other.minutes);
    }
    
    bool clock::operator!=(const clock& other) const {
        return (minutes != other.minutes);
    }
}  // namespace date_independent
