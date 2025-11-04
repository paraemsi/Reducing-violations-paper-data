#include "clock.h"

#include <iomanip>
#include <sstream>
#include <ostream>

namespace date_independent {

namespace {
constexpr int kMinutesPerHour = 60;
constexpr int kHoursPerDay = 24;
constexpr int kMinutesPerDay = kMinutesPerHour * kHoursPerDay;
}

int clock::normalize_minutes(int total_minutes) {
    int m = total_minutes % kMinutesPerDay;
    if (m < 0) m += kMinutesPerDay;
    return m;
}

clock::clock(int total_minutes_normalized)
    : minutes_{normalize_minutes(total_minutes_normalized)} {}

clock clock::at(int hour, int minute) {
    int total = hour * kMinutesPerHour + minute;
    return clock{normalize_minutes(total)};
}

clock clock::plus(int minutes) const {
    return clock{minutes_ + minutes};
}

clock clock::minus(int minutes) const {
    return plus(-minutes);
}

std::string clock::str() const {
    int hours = minutes_ / kMinutesPerHour;
    int mins = minutes_ % kMinutesPerHour;

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours
        << ":" << std::setw(2) << std::setfill('0') << mins;
    return oss.str();
}

bool clock::operator==(const clock& other) const {
    return minutes_ == other.minutes_;
}

std::ostream& operator<<(std::ostream& os, const clock& c) {
    return os << c.str();
}

}  // namespace date_independent
