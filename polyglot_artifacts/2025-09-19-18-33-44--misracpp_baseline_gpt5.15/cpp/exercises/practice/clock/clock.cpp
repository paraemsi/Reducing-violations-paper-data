#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {

namespace {
constexpr int kMinutesPerHour = 60;
constexpr int kMinutesPerDay = 24 * kMinutesPerHour;
}

int clock::normalize(int total_minutes) noexcept {
    int m = total_minutes % kMinutesPerDay;
    if (m < 0) m += kMinutesPerDay;
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
    return clock(0, minutes_ - minutes);
}

int clock::hour() const {
    return minutes_ / kMinutesPerHour;
}

int clock::minute() const {
    return minutes_ % kMinutesPerHour;
}

clock::operator std::string() const {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hour()
        << ":" << std::setfill('0') << std::setw(2) << minute();
    return oss.str();
}

bool operator==(const clock& lhs, const clock& rhs) {
    return lhs.minutes_ == rhs.minutes_;
}

bool operator!=(const clock& lhs, const clock& rhs) {
    return !(lhs == rhs);
}

std::string to_string(const clock& c) {
    return static_cast<std::string>(c);
}

}  // namespace date_independent
