#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {
    clock::clock(int minutes) : minutes(minutes) {}
    
    clock clock::at(int hours, int minutes) {
        int total_minutes = (hours * 60 + minutes) % (24 * 60);
        if (total_minutes < 0) {
            total_minutes += 24 * 60;
        }
        return clock(total_minutes);
    }
    
    clock clock::plus(int minutes_to_add) const {
        return clock::at(0, minutes + minutes_to_add);
    }
    
    clock clock::minus(int minutes_to_subtract) const {
        return clock::at(0, minutes - minutes_to_subtract);
    }
    
    clock::operator std::string() const {
        int hours = minutes / 60;
        int mins = minutes % 60;
        // Since minutes is always between 0-1439, hours will be between 0-23
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << hours << ":"
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
