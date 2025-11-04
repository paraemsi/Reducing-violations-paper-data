#include "clock.h"

#include <iomanip>
#include <sstream>
#include <string>

namespace date_independent {

int clock::normalize(int total_minutes) noexcept {
    constexpr int kDayMinutes = 24 * 60;
    int m = total_minutes % kDayMinutes;
    if (m < 0) {
        m += kDayMinutes;
    }
    return m;
}

clock clock::at(int hour, int minute) noexcept {
    const int total = hour * 60 + minute;
    return clock(normalize(total));
}

clock::clock(int total_minutes) noexcept
    : minutes_(normalize(total_minutes)) {}

clock clock::plus(int minutes) const noexcept {
    return clock(minutes_ + minutes);
}

clock clock::minus(int minutes) const noexcept {
    return clock(minutes_ - minutes);
}

std::string clock::str() const {
    const int hours = minutes_ / 60;
    const int mins = minutes_ % 60;

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours
        << ':'
        << std::setw(2) << std::setfill('0') << mins;
    return oss.str();
}

bool operator==(const clock& lhs, const clock& rhs) noexcept {
    return lhs.minutes_ == rhs.minutes_;
}

bool operator!=(const clock& lhs, const clock& rhs) noexcept {
    return !(lhs == rhs);
}

}  // namespace date_independent
