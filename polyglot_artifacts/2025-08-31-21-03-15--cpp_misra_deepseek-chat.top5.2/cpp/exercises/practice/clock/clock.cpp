#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {
    clock::clock(std::int32_t total_minutes) {
        // Normalize to be within 0-1439
        // Handle negative values by adding enough days to make it positive
        // To avoid integer overflow issues, we use modulo arithmetic
        total_minutes %= 1440;
        if (total_minutes < 0) {
            total_minutes += 1440;
        }
        minutes = total_minutes;
    }
    
    clock clock::at(std::int32_t hours, std::int32_t minutes) {
        // Convert hours and minutes to total minutes, then normalize
        std::int32_t total_minutes = (hours * 60) + minutes;
        // Normalize to be within 0-1439
        total_minutes %= 1440;
        if (total_minutes < 0) {
            total_minutes += 1440;
        }
        return clock(total_minutes);
    }
    
    clock clock::plus(std::int32_t add_minutes) const {
        // Add minutes and normalize
        // To prevent integer overflow, we can compute modulo 1440 at each step
        // Since minutes is always between 0-1439, adding add_minutes could be large
        // Let's compute the new total minutes modulo 1440
        std::int32_t new_minutes = (minutes + add_minutes) % 1440;
        if (new_minutes < 0) {
            new_minutes += 1440;
        }
        return clock(new_minutes);
    }
    
    clock clock::minus(std::int32_t sub_minutes) const {
        // Subtract minutes is the same as adding negative minutes
        return plus(-sub_minutes);
    }
    
    clock::operator std::string() const {
        std::int32_t hours = minutes / 60;
        std::int32_t mins = minutes % 60;
        // Since minutes is always between 0-1439, hours will be between 0-23
        
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
