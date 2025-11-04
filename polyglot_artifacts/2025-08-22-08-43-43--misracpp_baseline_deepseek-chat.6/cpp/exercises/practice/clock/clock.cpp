#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {
    clock::clock(int total_minutes) : minutes(total_minutes) {}
    
    clock clock::at(int hours, int minutes) {
        // Normalize to be within 0-1439
        int total_minutes = (hours * 60 + minutes) % 1440;
        if (total_minutes < 0) {
            total_minutes += 1440;
        }
        return clock(total_minutes);
    }
    
    clock clock::plus(int minutes_to_add) const {
        int total = minutes + minutes_to_add;
        total %= 1440;
        if (total < 0) {
            total += 1440;
        }
        return clock(total);
    }
    
    clock clock::minus(int minutes_to_subtract) const {
        // Reuse plus by adding negative minutes
        return plus(-minutes_to_subtract);
    }
    
    clock::operator std::string() const {
        int hrs = minutes / 60;
        int mins = minutes % 60;
        
        std::ostringstream oss;
        oss << std::setfill('0') << std::setw(2) << hrs << ":" 
            << std::setfill('0') << std::setw(2) << mins;
        return oss.str();
    }
    
    bool clock::operator==(const clock& other) const {
        return minutes == other.minutes;
    }
    
    bool clock::operator!=(const clock& other) const {
        return minutes != other.minutes;
    }
}  // namespace date_independent
