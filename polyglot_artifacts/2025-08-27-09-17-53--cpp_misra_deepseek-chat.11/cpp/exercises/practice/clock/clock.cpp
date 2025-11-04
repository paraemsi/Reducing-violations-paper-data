#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {
    clock::clock(std::int32_t minutes) : minutes_since_midnight(minutes) {}
    
    clock clock::at(std::int32_t hours, std::int32_t minutes) {
        // First, convert everything to total minutes
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
        // Subtract minutes by adding negative value
        return this->plus(-minutes_to_subtract);
    }
    
    clock::operator std::string() const {
        // Calculate hours and minutes
        std::int32_t hours = minutes_since_midnight / 60;
        std::int32_t minutes = minutes_since_midnight % 60;
        
        // Since minutes_since_midnight is always between 0 and 1439, hours will be between 0 and 23
        // So no need to check for negative values
        
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << hours << ":"
            << std::setw(2) << std::setfill('0') << minutes;
        return oss.str();
    }
    
    bool clock::operator==(const clock& other) const {
        return (minutes_since_midnight == other.minutes_since_midnight);
    }
    
    bool clock::operator!=(const clock& other) const {
        return !(*this == other);
    }
}  // namespace date_independent
