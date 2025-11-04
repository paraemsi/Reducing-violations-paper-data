#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

namespace {
constexpr int kMinutesPerDay = 24 * 60;

int normalize_minutes(int total) {
    total %= kMinutesPerDay;
    if (total < 0) {
        total += kMinutesPerDay;
    }
    return total;
}
}  // namespace

clock::clock(int total_minutes)
    : minutes_(normalize_minutes(total_minutes)) {}

clock clock::at(int hour, int minute) {
    const long total = static_cast<long>(hour) * 60L + static_cast<long>(minute);
    return clock(static_cast<int>(total));
}

clock clock::plus(int minutes) const {
    return clock(minutes_ + minutes);
}

clock::operator std::string() const {
    const int h = minutes_ / 60;
    const int m = minutes_ % 60;
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << h
        << ':' << std::setfill('0') << std::setw(2) << m;
    return oss.str();
}

bool operator==(const clock& lhs, const clock& rhs) {
    return lhs.minutes_ == rhs.minutes_;
}

bool operator!=(const clock& lhs, const clock& rhs) {
    return !(lhs == rhs);
}

}  // namespace date_independent
