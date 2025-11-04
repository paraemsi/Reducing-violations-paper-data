#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

#include <cmath>
namespace date_independent {
    clock::clock(std::int32_t total_minutes) : total_minutes(total_minutes) {}
    
    clock clock::at(std::int32_t hours, std::int32_t minutes) {
        // Convert everything to minutes
        std::int32_t total_minutes_from_input = (hours * 60) + minutes;
        // Normalize to be within 0-1439
        // Handle negative values by adding enough days
        std::int32_t normalized_minutes = total_minutes_from_input % 1440;
        if (normalized_minutes < 0) {
            normalized_minutes += 1440;
        }
        return clock(normalized_minutes);
    }
    
    clock clock::plus(std::int32_t minutes_to_add) const {
        // Since total_minutes is always between 0-1439, we can simply add and re-normalize
        return clock::at(0, total_minutes + minutes_to_add);
    }
    
    clock clock::minus(std::int32_t minutes_to_subtract) const {
        // Use plus with negative value
        return this->plus(-minutes_to_subtract);
    }
    
    clock::operator std::string() const {
        // Since total_minutes is always between 0-1439, hours will always be between 0-23
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
