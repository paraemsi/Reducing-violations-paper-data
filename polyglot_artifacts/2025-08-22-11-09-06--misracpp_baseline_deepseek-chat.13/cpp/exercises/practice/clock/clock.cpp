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

clock clock::at(int hour, int minute) {
    int total_minutes = hour * 60 + minute;
    return clock(total_minutes);
}

clock clock::plus(int minutes_to_add) const {
    return clock(minutes + minutes_to_add);
}

clock clock::minus(int minutes_to_subtract) const {
    return clock(minutes - minutes_to_subtract);
}

clock::operator std::string() const {
    int total_minutes = minutes;
    int hour = total_minutes / 60;
    int minute = total_minutes % 60;
    
    // Since total_minutes is always between 0 and 1439, hour will be between 0 and 23
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hour << ":"
        << std::setfill('0') << std::setw(2) << minute;
    return oss.str();
}

bool clock::operator==(const clock& other) const {
    return minutes == other.minutes;
}

bool clock::operator!=(const clock& other) const {
    return minutes != other.minutes;
}

}  // namespace date_independent
