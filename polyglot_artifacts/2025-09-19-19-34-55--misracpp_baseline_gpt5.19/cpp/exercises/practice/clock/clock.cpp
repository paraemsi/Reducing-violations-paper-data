#include "clock.h"

#include <iomanip>
#include <sstream>
#include <ostream>

namespace date_independent {

namespace {
constexpr int kMinutesPerHour = 60;
constexpr int kHoursPerDay = 24;
constexpr int kMinutesPerDay = kHoursPerDay * kMinutesPerHour;
}  // namespace

int clock::normalize(int total_minutes) {
    int m = total_minutes % kMinutesPerDay;
    if (m < 0) {
        m += kMinutesPerDay;
    }
    return m;
}

clock::clock(int hour, int minute)
    : minutes_(normalize(hour * kMinutesPerHour + minute)) {}

clock clock::at(int hour, int minute) {
    return clock(hour, minute);
}

clock clock::plus(int minutes) const {
    return clock(0, minutes_ + minutes);
}

clock clock::minus(int minutes) const {
    return plus(-minutes);
}

std::string clock::to_string() const {
    int hours = minutes_ / kMinutesPerHour;
    int mins  = minutes_ % kMinutesPerHour;

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hours
        << ":" << std::setfill('0') << std::setw(2) << mins;
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

std::ostream& operator<<(std::ostream& os, const clock& c) {
    return os << c.to_string();
}

}  // namespace date_independent
