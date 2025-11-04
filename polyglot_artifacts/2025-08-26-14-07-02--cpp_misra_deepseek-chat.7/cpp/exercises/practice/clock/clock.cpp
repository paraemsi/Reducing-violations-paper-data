#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {
    clock::clock(std::int32_t minutes) : total_minutes(minutes) {}
    
    clock clock::at(std::int32_t hours, std::int32_t minutes) {
        // Convert everything to minutes and normalize
        std::int32_t total_minutes = (hours * 60) + minutes;
        // Normalize to be within 0-1439
        total_minutes %= 1440;
        if (total_minutes < 0) {
            total_minutes += 1440;
        }
        return clock(total_minutes);
    }
    
    clock clock::plus(std::int32_t minutes) const {
        // Add minutes and normalize
        return clock::at(0, total_minutes + minutes);
    }
    
    clock clock::minus(std::int32_t minutes) const {
        // Subtract minutes and normalize
        return clock::at(0, total_minutes - minutes);
    }
    
    clock::operator std::string() const {
        // Always ensure total_minutes is normalized (though it should be)
        std::int32_t normalized_minutes = total_minutes % 1440;
        if (normalized_minutes < 0) {
            normalized_minutes += 1440;
        }
        std::int32_t hours = normalized_minutes / 60;
        std::int32_t minutes = normalized_minutes % 60;
        
        // Format the output
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << hours << ":"
            << std::setw(2) << std::setfill('0') << minutes;
        return oss.str();
    }
    
    bool clock::operator==(const clock& other) const {
        // Compare normalized times
        // Normalize both to 0-1439 range
        std::int32_t this_minutes = total_minutes % 1440;
        if (this_minutes < 0) {
            this_minutes += 1440;
        }
        std::int32_t other_minutes = other.total_minutes % 1440;
        if (other_minutes < 0) {
            other_minutes += 1440;
        }
        return this_minutes == other_minutes;
    }
    
    bool clock::operator!=(const clock& other) const {
        return !(*this == other);
    }
}  // namespace date_independent
