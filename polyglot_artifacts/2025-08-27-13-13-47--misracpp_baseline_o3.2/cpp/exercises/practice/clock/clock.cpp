#include "clock.h"
#include <iomanip>
#include <sstream>
#include <ostream>

namespace date_independent {

int clock::normalize(int minutes) {
    const int minutes_per_day = 24 * 60;
    minutes %= minutes_per_day;
    if (minutes < 0) {
        minutes += minutes_per_day;
    }
    return minutes;
}

clock::clock(int hour, int minute)
    : minutes_since_midnight_(normalize(hour * 60 + minute)) {}

clock clock::at(int hour, int minute) {
    return clock(hour, minute);
}

clock clock::plus(int minute_delta) const {
    return clock(0, minutes_since_midnight_ + minute_delta);
}

clock clock::minus(int minute_delta) const {
    return plus(-minute_delta);
}

clock::operator std::string() const {
    std::ostringstream oss;
    int hours = minutes_since_midnight_ / 60;
    int minutes = minutes_since_midnight_ % 60;
    oss << std::setfill('0') << std::setw(2) << hours << ':'
        << std::setfill('0') << std::setw(2) << minutes;
    return oss.str();
}

std::string clock::to_string() const {
    return static_cast<std::string>(*this);
}

bool clock::operator==(const clock &rhs) const {
    return minutes_since_midnight_ == rhs.minutes_since_midnight_;
}

std::ostream &operator<<(std::ostream &os, const clock &c) {
    return os << c.to_string();
}

}  // namespace date_independent
