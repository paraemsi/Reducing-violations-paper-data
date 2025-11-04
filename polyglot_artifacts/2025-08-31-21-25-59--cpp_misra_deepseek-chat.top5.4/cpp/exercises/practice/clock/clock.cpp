#include "clock.h"
#include <string>
#include <sstream>
#include <iomanip>

namespace date_independent {
    void clock::normalize() {
        // Normalize total_minutes to be within 0-1439 (minutes in a day)
        // Handle negative values by adding enough days
        if (total_minutes < 0) {
            total_minutes = ((total_minutes % 1440) + 1440) % 1440;
        } else {
            total_minutes %= 1440;
        }
        // Ensure it's positive
        if (total_minutes < 0) {
            total_minutes += 1440;
        }
    }

    clock::clock(std::int32_t total_minutes) : total_minutes(total_minutes) {
        normalize();
    }
    
    clock clock::at(std::int32_t hours, std::int32_t minutes) {
        // Convert hours and minutes to total minutes
        std::int32_t total = (hours * 60) + minutes;
        return clock(total);
    }
    
    clock clock::plus(std::int32_t minutes) const {
        return clock(total_minutes + minutes);
    }
    
    clock clock::minus(std::int32_t minutes) const {
        return clock(total_minutes - minutes);
    }
    
    clock::operator std::string() const {
        std::int32_t hours = total_minutes / 60;
        std::int32_t mins = total_minutes % 60;
        // Ensure hours are within 0-23 by taking modulo 24
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
        return (total_minutes == other.total_minutes);
    }
    
    bool clock::operator!=(const clock& other) const {
        return (total_minutes != other.total_minutes);
    }
}  // namespace date_independent
