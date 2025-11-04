#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {
    clock::clock(int total_minutes) {
        // Normalize to be within 0-1439 minutes (0-23:59)
        total_minutes %= 1440;
        if (total_minutes < 0) {
            total_minutes += 1440;
        }
        this->minutes = total_minutes;
    }
    
    clock clock::at(int hours, int minutes) {
        int total_minutes = hours * 60 + minutes;
        return clock(total_minutes);
    }
    
    clock clock::plus(int minutes_to_add) const {
        return clock(this->minutes + minutes_to_add);
    }
    
    clock clock::minus(int minutes_to_subtract) const {
        return clock(this->minutes - minutes_to_subtract);
    }
    
    clock::operator std::string() const {
        int hrs = minutes / 60;
        int mins = minutes % 60;
        
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << hrs << ":"
            << std::setw(2) << std::setfill('0') << mins;
        return oss.str();
    }
    
    bool clock::operator==(const clock& other) const {
        return this->minutes == other.minutes;
    }
    
    bool clock::operator!=(const clock& other) const {
        return !(*this == other);
    }
}  // namespace date_independent
