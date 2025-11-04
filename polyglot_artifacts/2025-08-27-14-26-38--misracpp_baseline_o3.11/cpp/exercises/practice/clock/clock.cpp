#include "clock.h"
#include <iomanip>
#include <sstream>
#include <string>

namespace date_independent {

int clock::normalize(int minutes) {
    constexpr int minutes_per_day = 24 * 60;
    minutes %= minutes_per_day;
    if (minutes < 0) {
        minutes += minutes_per_day;
    }
    return minutes;
}

clock::clock(int hour, int minute)
    : minutes_{normalize(hour * 60 + minute)} {}

clock clock::at(int hour, int minute) {
    return clock{hour, minute};
}

clock clock::plus(int minute) const {
    return clock{0, minutes_ + minute};
}

clock clock::minus(int minute) const {
    return clock{0, minutes_ - minute};
}

clock::operator std::string() const {
    int hour = minutes_ / 60;
    int minute = minutes_ % 60;
    std::ostringstream os;
    os << std::setfill('0') << std::setw(2) << hour << ':'
       << std::setfill('0') << std::setw(2) << minute;
    return os.str();
}

std::string clock::to_string() const {
    // Re-use the implicit conversion operator to avoid duplicating logic.
    return static_cast<std::string>(*this);
}

bool clock::operator==(const clock& other) const {
    return minutes_ == other.minutes_;
}

bool clock::operator!=(const clock& other) const {
    return !(*this == other);
}

}  // namespace date_independent
