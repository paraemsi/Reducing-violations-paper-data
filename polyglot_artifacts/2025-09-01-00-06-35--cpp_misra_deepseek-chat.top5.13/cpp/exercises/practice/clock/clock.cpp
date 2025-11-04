#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {
    clock::clock(std::int32_t minutes) : total_minutes(minutes) {}
    
    clock clock::at(std::int32_t hours, std::int32_t minutes) {
        // Calculate total minutes
        std::int32_t total_minutes = hours * 60 + minutes;
        // Normalize to be within 0-1439 minutes
        total_minutes %= 1440;
        if (total_minutes < 0) {
            total_minutes += 1440;
        }
        return clock(total_minutes);
    }
    
    clock clock::plus(std::int32_t minutes) const {
        // Add minutes and normalize
        std::int32_t new_minutes = (total_minutes + minutes) % 1440;
        if (new_minutes < 0) {
            new_minutes += 1440;
        }
        return clock(new_minutes);
    }
    
    clock clock::minus(std::int32_t minutes) const {
        // Subtract minutes and normalize
        std::int32_t new_minutes = (total_minutes - minutes) % 1440;
        if (new_minutes < 0) {
            new_minutes += 1440;
        }
        return clock(new_minutes);
    }
    
    clock::operator std::string() const {
        // Since total_minutes is always between 0 and 1439, we can safely compute hours and minutes
        std::int32_t hours = total_minutes / 60;
        std::int32_t mins = total_minutes % 60;
        
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << hours << ":"
            << std::setw(2) << std::setfill('0') << mins;
        return oss.str();
    }
    
    bool clock::operator==(const clock& other) const {
        return total_minutes == other.total_minutes;
    }
    
    bool clock::operator!=(const clock& other) const {
        return total_minutes != other.total_minutes;
    }
}  // namespace date_independent
