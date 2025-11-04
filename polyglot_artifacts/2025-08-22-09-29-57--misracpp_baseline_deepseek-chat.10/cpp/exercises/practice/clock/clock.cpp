#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {
    clock::clock(int total_minutes) : minutes(total_minutes) {}
    
    clock clock::at(int hours, int minutes) {
        int total_minutes = (hours * 60 + minutes) % 1440;
        if (total_minutes < 0) {
            total_minutes += 1440;
        }
        return clock(total_minutes);
    }
    
    clock clock::plus(int minutes_to_add) const {
        return clock::at(0, minutes + minutes_to_add);
    }
    
    clock clock::minus(int minutes_to_subtract) const {
        return plus(-minutes_to_subtract);
    }
    
    clock::operator std::string() const {
        int total_minutes = minutes;
        // Ensure it's positive
        if (total_minutes < 0) {
            total_minutes = (total_minutes % 1440 + 1440) % 1440;
        }
        int hrs = total_minutes / 60;
        int mins = total_minutes % 60;
        // Since total_minutes is always between 0-1439, hrs will be between 0-23
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << hrs << ":" 
            << std::setw(2) << std::setfill('0') << mins;
        return oss.str();
    }
    
    bool clock::operator==(const clock& other) const {
        return minutes == other.minutes;
    }
    
    bool clock::operator!=(const clock& other) const {
        return !(*this == other);
    }
}  // namespace date_independent
