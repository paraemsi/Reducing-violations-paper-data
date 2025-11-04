#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {

namespace {
    constexpr int kMinutesPerDay = 24 * 60;
}

int clock::normalize_minutes(int minutes) {
    int result = minutes % kMinutesPerDay;
    if (result < 0) result += kMinutesPerDay;
    return result;
}

clock::clock(int hour, int minute)
    : minutes_from_midnight_(normalize_minutes(hour * 60 + minute)) {}

clock clock::at(int hour, int minute) {
    return clock(hour, minute);
}

clock clock::plus(int minutes) const {
    int total = normalize_minutes(minutes_from_midnight_ + minutes);
    int h = total / 60;
    int m = total % 60;
    return clock(h, m);
}

clock clock::minus(int minutes) const {
    return plus(-minutes);
}

clock::operator std::string() const {
    return str();
}

std::string clock::str() const {
    int h = minutes_from_midnight_ / 60;
    int m = minutes_from_midnight_ % 60;
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << h
        << ':' << std::setfill('0') << std::setw(2) << m;
    return oss.str();
}

bool operator==(const clock& lhs, const clock& rhs) {
    return lhs.minutes_from_midnight_ == rhs.minutes_from_midnight_;
}

bool operator!=(const clock& lhs, const clock& rhs) {
    return !(lhs == rhs);
}

}  // namespace date_independent
