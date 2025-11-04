#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(int total_minutes) : minutes_{normalize(total_minutes)} {}

int clock::normalize(int total_minutes) {
    const int day = 24 * 60;
    int m = total_minutes % day;
    if (m < 0) m += day;
    return m;
}

clock clock::at(int hour, int minute) {
    return clock(hour * 60 + minute);
}

clock clock::plus(int minute) const {
    return clock(minutes_ + minute);
}

std::string clock::to_string() const {
    int h = minutes_ / 60;
    int m = minutes_ % 60;
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << h
        << ':'
        << std::setw(2) << std::setfill('0') << m;
    return oss.str();
}

bool operator==(const clock& lhs, const clock& rhs) { return lhs.minutes_ == rhs.minutes_; }
bool operator!=(const clock& lhs, const clock& rhs) { return !(lhs == rhs); }

}  // namespace date_independent
