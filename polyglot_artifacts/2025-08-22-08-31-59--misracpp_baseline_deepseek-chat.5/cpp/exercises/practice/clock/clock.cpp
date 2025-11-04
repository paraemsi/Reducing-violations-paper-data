#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {
    clock::clock(int total_minutes) : minutes(total_minutes) {
        normalize();
    }
    
    void clock::normalize() {
        // Handle negative minutes by making them positive within a day
        minutes %= 1440; // 24*60 minutes per day
        if (minutes < 0) {
            minutes += 1440;
        }
    }
    
    clock clock::at(int hours, int minutes) {
        int total_minutes = hours * 60 + minutes;
        return clock(total_minutes);
    }
    
    clock clock::plus(int minutes_to_add) const {
        return clock(minutes + minutes_to_add);
    }
    
    clock clock::minus(int minutes_to_subtract) const {
        return clock(minutes - minutes_to_subtract);
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
        return minutes == other.minutes;
    }
    
    bool clock::operator!=(const clock& other) const {
        return minutes != other.minutes;
    }
}  // namespace date_independent
