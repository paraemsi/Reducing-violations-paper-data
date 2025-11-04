#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

clock clock::at(int hour, int minute) {
    return clock(hour, minute);
}

clock::clock(int hour, int minute)
    : minutes_(normalize_minutes(hour * 60 + minute)) {}

int clock::normalize_minutes(int total_minutes) {
    constexpr int day = 24 * 60;
    int m = total_minutes % day;
    if (m < 0) m += day;
    return m;
}

clock clock::plus(int minutes) const {
    return clock(0, minutes_ + minutes);
}

clock clock::minus(int minutes) const {
    return plus(-minutes);
}

clock::operator std::string() const {
    int h = minutes_ / 60;
    int m = minutes_ % 60;
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << h << ":"
        << std::setfill('0') << std::setw(2) << m;
    return oss.str();
}

bool clock::operator==(const clock& other) const {
    return minutes_ == other.minutes_;
}

bool clock::operator!=(const clock& other) const {
    return !(*this == other);
}

}  // namespace date_independent
