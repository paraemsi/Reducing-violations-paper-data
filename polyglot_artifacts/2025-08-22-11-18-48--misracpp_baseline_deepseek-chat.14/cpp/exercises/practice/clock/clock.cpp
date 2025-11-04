#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(int total_minutes) {
    // Normalize to be within 0-1439 minutes
    minutes = total_minutes % (24 * 60);
    if (minutes < 0) {
        minutes += 24 * 60;
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
    
    // Format to HH:MM
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
