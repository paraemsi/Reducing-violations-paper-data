#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {
    clock::clock(minute_t minutes) : total_minutes(0) {
        // Ensure the total minutes is always positive and within a 24-hour period
        // Using modulo arithmetic to wrap around
        minute_t mod = minutes % 1440;
        if (mod < 0) {
            mod += 1440;
        }
        total_minutes = mod;
    }
    
    clock clock::at(minute_t hours, minute_t minutes) {
        // Convert hours to minutes and add to minutes
        minute_t total_minutes_from_input = (hours * 60) + minutes;
        return clock(total_minutes_from_input);
    }
    
    clock clock::plus(minute_t minutes) const {
        return clock(total_minutes + minutes);
    }
    
    clock clock::minus(minute_t minutes) const {
        return clock(total_minutes - minutes);
    }
    
    clock::operator std::string() const {
        // Since total_minutes is always normalized to be between 0-1439
        // hours will always be between 0-23, and minutes between 0-59
        minute_t hours = total_minutes / 60;
        minute_t mins = total_minutes % 60;
        
        // Format to HH:MM
        std::ostringstream oss;
        oss << std::setfill('0') << std::setw(2) << hours << ":"
            << std::setfill('0') << std::setw(2) << mins;
        return oss.str();
    }
    
    bool clock::operator==(const clock& other) const {
        return (total_minutes == other.total_minutes);
    }
    
    bool clock::operator!=(const clock& other) const {
        return (total_minutes != other.total_minutes);
    }
}  // namespace date_independent
