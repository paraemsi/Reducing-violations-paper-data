#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {
    clock::clock(std::int32_t minutes) : total_minutes(minutes) {}
    
    clock clock::at(std::int32_t hours, std::int32_t minutes) {
        // Convert everything to minutes
        std::int32_t total_minutes = (hours * 60) + minutes;
        // Normalize to be within 0-1439
        // Handle negative values by adding enough days to make it positive
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
        // Ensure total_minutes is always between 0 and 1439
        std::int32_t normalized_minutes = total_minutes;
        if (normalized_minutes < 0) {
            normalized_minutes = (normalized_minutes % 1440) + 1440;
        }
        normalized_minutes %= 1440;
        
        std::int32_t hours = normalized_minutes / 60;
        std::int32_t mins = normalized_minutes % 60;
        
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << hours << ":"
            << std::setw(2) << std::setfill('0') << mins;
        return oss.str();
    }
    
    bool clock::operator==(const clock& other) const {
        // Compare normalized times
        std::int32_t this_normalized = total_minutes % 1440;
        if (this_normalized < 0) {
            this_normalized += 1440;
        }
        
        std::int32_t other_normalized = other.total_minutes % 1440;
        if (other_normalized < 0) {
            other_normalized += 1440;
        }
        
        return (this_normalized == other_normalized);
    }
    
    bool clock::operator!=(const clock& other) const {
        return !(*this == other);
    }
}  // namespace date_independent
