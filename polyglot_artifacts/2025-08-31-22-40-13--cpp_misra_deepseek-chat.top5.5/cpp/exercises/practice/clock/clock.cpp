#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {
    clock::clock(std::int32_t minutes) : total_minutes(minutes) {}
    
    clock clock::at(std::int32_t hours, std::int32_t minutes) {
        // First, compute total minutes
        std::int32_t total_minutes_from_input = (hours * 60) + minutes;
        // Normalize to be within 0-1439
        total_minutes_from_input %= 1440;
        if (total_minutes_from_input < 0) {
            total_minutes_from_input += 1440;
        }
        return clock(total_minutes_from_input);
    }
    
    clock clock::plus(std::int32_t minutes) const {
        // Handle large numbers by using modulo arithmetic
        // First, compute the new total minutes and normalize to a positive value within 0-1439
        std::int32_t new_minutes = (total_minutes + minutes) % 1440;
        if (new_minutes < 0) {
            new_minutes += 1440;
        }
        return clock(new_minutes);
    }
    
    clock clock::minus(std::int32_t minutes) const {
        // Reuse plus by adding negative minutes
        return this->plus(-minutes);
    }
    
    clock::operator std::string() const {
        // Since total_minutes is always between 0 and 1439, we can directly compute hours and minutes
        std::int32_t hours = total_minutes / 60;
        std::int32_t mins = total_minutes % 60;
        // Ensure hours is within 0-23 (always true due to normalization)
        
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << hours << ":"
            << std::setw(2) << std::setfill('0') << mins;
        return oss.str();
    }
    
    bool clock::operator==(const clock& other) const {
        return total_minutes == other.total_minutes;
    }
    
    bool clock::operator!=(const clock& other) const {
        return !(*this == other);
    }
}  // namespace date_independent
