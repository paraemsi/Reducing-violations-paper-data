#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

namespace {
    // Normalize any integer to [0, 1440)
    inline int normalize_total_minutes(long long total_minutes) {
        const int day_minutes = 24 * 60;
        int mod = static_cast<int>(total_minutes % day_minutes);
        if (mod < 0) mod += day_minutes;
        return mod;
    }
}

int clock::normalize(int hour, int minute) {
    long long total = static_cast<long long>(hour) * 60 + minute;
    return normalize_total_minutes(total);
}

clock::clock(int hour, int minute)
    : minutes_(normalize(hour, minute)) {}

clock::clock(int total_minutes, bool /*normalized_tag*/)
    : minutes_(normalize_total_minutes(total_minutes)) {}

clock clock::at(int hour, int minute) {
    return clock(hour, minute);
}

clock clock::plus(int minutes) const {
    return clock(minutes_ + minutes, true);
}

clock clock::minus(int minutes) const {
    return plus(-minutes);
}

std::string clock::str() const {
    int hours = minutes_ / 60;
    int mins = minutes_ % 60;
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hours
        << ':'
        << std::setfill('0') << std::setw(2) << mins;
    return oss.str();
}

bool clock::operator==(const clock& other) const {
    return minutes_ == other.minutes_;
}

}  // namespace date_independent
