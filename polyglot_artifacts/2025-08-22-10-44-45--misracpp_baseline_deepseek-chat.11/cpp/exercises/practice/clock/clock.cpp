#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {
    clock::clock(int minutes) : total_minutes(minutes) {
        // Normalize to be within 0-1439 minutes (0-23:59)
        total_minutes %= 1440;
        if (total_minutes < 0) {
            total_minutes += 1440;
        }
    }
    
    clock clock::at(int hours, int minutes) {
        int total = hours * 60 + minutes;
        return clock(total);
    }
    
    clock clock::plus(int minutes_to_add) const {
        return clock(total_minutes + minutes_to_add);
    }
    
    clock clock::minus(int minutes_to_subtract) const {
        return clock(total_minutes - minutes_to_subtract);
    }
    
    clock::operator std::string() const {
        int hrs = total_minutes / 60;
        int mins = total_minutes % 60;
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << hrs << ":"
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
