#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {

namespace {
constexpr int kMinutesPerDay = 24 * 60;
constexpr int kMinutesPerHour = 60;
}

int Clock::normalize(int total_minutes) noexcept {
    int m = total_minutes % kMinutesPerDay;
    if (m < 0) m += kMinutesPerDay;
    return m;
}

Clock::Clock(int total_minutes)
    : minutes_from_midnight_{normalize(total_minutes)} {}

Clock Clock::at(int hour, int minute) {
    int total = hour * kMinutesPerHour + minute;
    return Clock{total};
}

Clock Clock::plus(int minutes) const {
    return Clock{minutes_from_midnight_ + minutes};
}

Clock Clock::minus(int minutes) const {
    return Clock{minutes_from_midnight_ - minutes};
}

std::string Clock::str() const {
    int h = minutes_from_midnight_ / kMinutesPerHour;
    int m = minutes_from_midnight_ % kMinutesPerHour;
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << h << ":" << std::setw(2) << m;
    return oss.str();
}

Clock::operator std::string() const {
    return str();
}

bool Clock::operator==(const Clock& other) const noexcept {
    return minutes_from_midnight_ == other.minutes_from_midnight_;
}

bool Clock::operator!=(const Clock& other) const noexcept {
    return !(*this == other);
}

namespace clock {
Clock at(int hour, int minute) {
    return Clock::at(hour, minute);
}
}  // namespace clock

}  // namespace date_independent
