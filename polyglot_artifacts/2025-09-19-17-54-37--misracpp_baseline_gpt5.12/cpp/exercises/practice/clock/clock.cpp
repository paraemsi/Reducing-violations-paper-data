#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

int clock::normalize_minutes(int minutes) {
    constexpr int kDay = 24 * 60;
    int result = minutes % kDay;
    if (result < 0) result += kDay;
    return result;
}

clock::clock(int hour, int minute)
    : minutes_since_midnight_{normalize_minutes(hour * 60 + minute)} {}

clock clock::at(int hour, int minute) {
    return clock(hour, minute);
}

clock clock::plus(int minutes) const {
    return clock(0, minutes_since_midnight_ + minutes);
}

clock::operator std::string() const {
    int hour = minutes_since_midnight_ / 60;
    int minute = minutes_since_midnight_ % 60;
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hour
        << ":" << std::setw(2) << minute;
    return oss.str();
}

std::string clock::to_string() const {
    return static_cast<std::string>(*this);
}

bool clock::operator==(const clock& other) const {
    return minutes_since_midnight_ == other.minutes_since_midnight_;
}

bool clock::operator!=(const clock& other) const {
    return !(*this == other);
}


}  // namespace date_independent
