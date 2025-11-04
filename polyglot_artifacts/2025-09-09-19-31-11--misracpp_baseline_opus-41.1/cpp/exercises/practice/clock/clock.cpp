#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {

clock clock::at(int hours, int minutes) {
    return clock(hours, minutes);
}

clock::clock(int hours, int minutes) {
    total_minutes = hours * 60 + minutes;
    normalize();
}

clock clock::plus(int minutes) const {
    clock result(0, total_minutes + minutes);
    return result;
}

clock clock::minus(int minutes) const {
    clock result(0, total_minutes - minutes);
    return result;
}

bool clock::operator==(const clock& other) const {
    return total_minutes == other.total_minutes;
}

bool clock::operator!=(const clock& other) const {
    return !(*this == other);
}

clock::operator std::string() const {
    int hours = total_minutes / 60;
    int minutes = total_minutes % 60;
    
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hours << ":"
        << std::setfill('0') << std::setw(2) << minutes;
    return oss.str();
}

void clock::normalize() {
    // Handle negative minutes
    while (total_minutes < 0) {
        total_minutes += 1440;  // Add 24 hours worth of minutes
    }
    
    // Handle overflow beyond 24 hours
    total_minutes = total_minutes % 1440;
}

}  // namespace date_independent
