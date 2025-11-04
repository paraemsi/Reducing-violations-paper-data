#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {

static constexpr int kMinutesPerDay = 24 * 60;

int clock::normalize_minutes(int total_minutes) {
    int m = total_minutes % kMinutesPerDay;
    if (m < 0) m += kMinutesPerDay;
    return m;
}

clock::clock(int hour, int minute)
    : minutes_(normalize_minutes(hour * 60 + minute)) {}

clock clock::at(int hour, int minute) {
    return clock(hour, minute);
}

clock clock::plus(int minutes) const {
    return clock(0, minutes_ + minutes);
}

clock::operator std::string() const {
    int hour = minutes_ / 60;
    int minute = minutes_ % 60;
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hour
        << ":" << std::setw(2) << std::setfill('0') << minute;
    return oss.str();
}

bool operator==(const clock& lhs, const clock& rhs) {
    return lhs.minutes_ == rhs.minutes_;
}

bool operator!=(const clock& lhs, const clock& rhs) {
    return !(lhs == rhs);
}

}  // namespace date_independent
