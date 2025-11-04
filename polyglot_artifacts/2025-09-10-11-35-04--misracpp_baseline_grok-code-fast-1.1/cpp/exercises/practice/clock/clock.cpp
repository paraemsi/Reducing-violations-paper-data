#include "clock.h"
#include <sstream>
#include <iomanip>

namespace date_independent {

clock::clock(int h, int m) : hours(h), minutes(m) {
    normalize();
}

void clock::normalize() {
    int total_minutes = hours * 60 + minutes;
    total_minutes %= 1440;  // 24 * 60 = 1440 minutes in a day
    if (total_minutes < 0) {
        total_minutes += 1440;
    }
    hours = total_minutes / 60;
    minutes = total_minutes % 60;
}

clock clock::at(int hour, int minute) {
    return clock(hour, minute);
}

clock clock::plus(int mins) const {
    return clock(hours, minutes + mins);
}

clock clock::minus(int mins) const {
    return clock(hours, minutes - mins);
}

bool clock::operator==(const clock& other) const {
    return hours == other.hours && minutes == other.minutes;
}

std::string clock::to_string() const {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hours << ":" << std::setfill('0') << std::setw(2) << minutes;
    return oss.str();
}

}  // namespace date_independent
