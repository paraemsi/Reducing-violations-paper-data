#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

int clock::normalize_minutes(int total_minutes) {
    constexpr int minutes_per_day = 24 * 60;
    int m = total_minutes % minutes_per_day;
    if (m < 0) {
        m += minutes_per_day;
    }
    return m;
}

clock::clock(int hour, int minute)
    : minutes_{normalize_minutes(hour * 60 + minute)} {}

clock clock::at(int hour, int minute) {
    return clock(hour, minute);
}

clock clock::plus(int minutes) const {
    return clock(0, minutes_ + minutes);
}

clock clock::minus(int minutes) const {
    return clock(0, minutes_ - minutes);
}

std::string clock::to_string() const {
    int hours = minutes_ / 60;
    int mins = minutes_ % 60;

    std::ostringstream os;
    os << std::setfill('0') << std::setw(2) << hours
       << ":" << std::setfill('0') << std::setw(2) << mins;
    return os.str();
}

bool operator==(const clock& lhs, const clock& rhs) {
    return lhs.minutes_ == rhs.minutes_;
}

bool operator!=(const clock& lhs, const clock& rhs) {
    return !(lhs == rhs);
}

}  // namespace date_independent
