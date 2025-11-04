#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(int total_minutes)
    : minutes_(normalize_minutes(total_minutes)) {}

int clock::normalize_minutes(int total) {
    const int day = 24 * 60;  // minutes per day
    int m = total % day;
    if (m < 0) {
        m += day;
    }
    return m;
}

clock clock::at(int hour, int minute) {
    return clock(hour * 60 + minute);
}

clock clock::plus(int minutes) const {
    return clock(minutes_ + minutes);
}

clock clock::minus(int minutes) const {
    return clock(minutes_ - minutes);
}

std::string clock::str() const {
    int hour = minutes_ / 60;
    int minute = minutes_ % 60;

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hour
        << ':' << std::setw(2) << std::setfill('0') << minute;
    return oss.str();
}

clock::operator std::string() const {
    return str();
}

bool operator==(const clock& lhs, const clock& rhs) {
    return lhs.minutes_ == rhs.minutes_;
}

bool operator!=(const clock& lhs, const clock& rhs) {
    return !(lhs == rhs);
}

}  // namespace date_independent
