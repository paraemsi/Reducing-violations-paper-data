#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(int total_minutes) {
    // Normalize to a positive value within a day
    total_minutes %= 1440;
    if (total_minutes < 0) {
        total_minutes += 1440;
    }
    minutes = total_minutes;
}

clock clock::at(int hours, int minutes) {
    // Convert hours and minutes to total minutes and normalize
    int total_minutes = (hours * 60 + minutes) % 1440;
    if (total_minutes < 0) {
        total_minutes += 1440;
    }
    return clock(total_minutes);
}

clock clock::plus(int min) const {
    return clock(minutes + min);
}

clock clock::minus(int min) const {
    return clock(minutes - min);
}

clock::operator std::string() const {
    int h = minutes / 60;
    int m = minutes % 60;
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << h << ":" 
        << std::setw(2) << std::setfill('0') << m;
    return oss.str();
}

bool clock::operator==(const clock& other) const {
    return minutes == other.minutes;
}

bool clock::operator!=(const clock& other) const {
    return minutes != other.minutes;
}

}  // namespace date_independent
