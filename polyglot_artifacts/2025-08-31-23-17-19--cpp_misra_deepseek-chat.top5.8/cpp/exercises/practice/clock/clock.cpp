#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {
    clock::clock(std::int32_t minutes) : total_minutes(minutes) {}
    
    clock clock::at(std::int32_t hours, std::int32_t minutes) {
        // Normalize to a positive number of minutes within a day
        std::int32_t total = (hours * 60) + minutes;
        // Handle negative values by adding enough days to make it positive
        total %= (24 * 60);
        if (total < 0) {
            total += (24 * 60);
        }
        return clock(total);
    }
    
    clock clock::plus(std::int32_t minutes) const {
        std::int32_t new_minutes = total_minutes + minutes;
        // Normalize to be within 0-1439
        new_minutes %= (24 * 60);
        if (new_minutes < 0) {
            new_minutes += (24 * 60);
        }
        return clock(new_minutes);
    }
    
    clock clock::minus(std::int32_t minutes) const {
        // Reuse plus by adding negative minutes
        return plus(-minutes);
    }
    
    clock::operator std::string() const {
        std::int32_t hours = total_minutes / 60;
        std::int32_t minutes = total_minutes % 60;
        
        // Format to two digits each
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << hours << ":"
            << std::setw(2) << std::setfill('0') << minutes;
        return oss.str();
    }
    
    bool clock::operator==(const clock& other) const {
        return (total_minutes == other.total_minutes);
    }
    
    bool clock::operator!=(const clock& other) const {
        return (total_minutes != other.total_minutes);
    }
}  // namespace date_independent
