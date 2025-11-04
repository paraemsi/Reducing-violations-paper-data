#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

int clock::normalize_minutes(int total_minutes) {
    constexpr int minutes_per_day = 24 * 60;
    int m = total_minutes % minutes_per_day;
    if (m < 0) {
        m += minutes_per_day;
    }
    return m;
}

clock::clock(int hour, int minute)
    : minutes_{normalize_minutes(hour * 60 + minute)} {}

clock clock::at(int hour, int minute) {
    return clock(hour, minute);
}

clock clock::plus(int minute) const {
    return clock(0, minutes_ + minute);
}

clock clock::minus(int minute) const {
    return clock(0, minutes_ - minute);
}

std::string clock::to_string() const {
    int hour = minutes_ / 60;
    int minute = minutes_ % 60;

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hour
        << ":" << std::setfill('0') << std::setw(2) << minute;
    return oss.str();
}

clock::operator std::string() const {
    return to_string();
}

bool clock::operator==(const clock& other) const {
    return minutes_ == other.minutes_;
}

bool clock::operator!=(const clock& other) const {
    return !(*this == other);
}

}  // namespace date_independent
