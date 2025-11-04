#include "clock.h"

#include <iomanip>
#include <sstream>
#include <ostream>

namespace date_independent {

namespace {
constexpr int kMinutesPerDay = 24 * 60;
}

// Normalize minutes to the range [0, kMinutesPerDay)
int clock::normalize(int total_minutes) noexcept {
    int m = total_minutes % kMinutesPerDay;
    if (m < 0) m += kMinutesPerDay;
    return m;
}

clock::clock(int total_minutes) noexcept
    : minutes_from_midnight_(normalize(total_minutes)) {}

clock clock::at(int hour, int minute) noexcept {
    int total = hour * 60 + minute;
    return clock(total);
}

clock clock::plus(int minutes) const noexcept {
    return clock(minutes_from_midnight_ + minutes);
}

std::string clock::to_string() const {
    int hours = minutes_from_midnight_ / 60;
    int minutes = minutes_from_midnight_ % 60;
    std::ostringstream os;
    os << std::setw(2) << std::setfill('0') << hours
       << ":" << std::setw(2) << std::setfill('0') << minutes;
    return os.str();
}

clock::operator std::string() const {
    return to_string();
}

bool clock::operator==(const clock& other) const noexcept {
    return minutes_from_midnight_ == other.minutes_from_midnight_;
}

bool clock::operator!=(const clock& other) const noexcept {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const clock& c) {
    return os << c.to_string();
}

}  // namespace date_independent
