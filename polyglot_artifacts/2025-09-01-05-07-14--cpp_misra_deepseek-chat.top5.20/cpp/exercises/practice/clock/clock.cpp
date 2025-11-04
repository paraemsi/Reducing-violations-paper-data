#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {
    clock::clock(std::int32_t minutes) : total_minutes(minutes) {}
    
    clock clock::at(std::int32_t hours, std::int32_t minutes) {
        // Convert everything to minutes and normalize to be within 0-1439
        std::int32_t total_minutes_from_input = (hours * 60) + minutes;
        // Normalize to a positive number within a day
        // Modulo operation can give negative results, so adjust if necessary
        std::int32_t normalized_minutes = total_minutes_from_input % 1440;
        if (normalized_minutes < 0) {
            normalized_minutes += 1440;
        }
        return clock(normalized_minutes);
    }
    
    clock clock::plus(std::int32_t minutes) const {
        // Handle large numbers by taking modulo 1440 to wrap around days
        // Ensure the result is always positive
        std::int32_t new_minutes = (total_minutes + minutes) % 1440;
        if (new_minutes < 0) {
            new_minutes += 1440;
        }
        return clock(new_minutes);
    }
    
    clock clock::minus(std::int32_t minutes) const {
        // To subtract, it's the same as adding negative minutes
        return this->plus(-minutes);
    }
    
    clock::operator std::string() const {
        std::int32_t hours = total_minutes / 60;
        std::int32_t mins = total_minutes % 60;
        
        // Format to HH:MM
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
