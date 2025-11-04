#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

namespace {
    constexpr int kDayMinutes = 24 * 60;

    inline int mod_day(int minutes) {
        // Proper modulo for negatives, result in [0, kDayMinutes)
        int m = minutes % kDayMinutes;
        if (m < 0) m += kDayMinutes;
        return m;
    }
}

int clock::normalize(int hour, int minute) {
    return mod_day(hour * 60 + minute);
}

clock::clock(int hour, int minute)
    : total_minutes_{normalize(hour, minute)} {}

clock clock::at(int hour, int minute) {
    return clock(hour, minute);
}

clock clock::plus(int minutes) const {
    // Add minutes and normalize
    return clock(0, total_minutes_ + minutes);
}

clock clock::minus(int minutes) const {
    return plus(-minutes);
}

clock::operator std::string() const {
    int hours = total_minutes_ / 60;
    int mins = total_minutes_ % 60;

    std::ostringstream os;
    os << std::setfill('0') << std::setw(2) << hours
       << ":" << std::setfill('0') << std::setw(2) << mins;
    return os.str();
}

bool clock::operator==(const clock& other) const {
    return total_minutes_ == other.total_minutes_;
}

bool clock::operator!=(const clock& other) const {
    return !(*this == other);
}

}  // namespace date_independent
