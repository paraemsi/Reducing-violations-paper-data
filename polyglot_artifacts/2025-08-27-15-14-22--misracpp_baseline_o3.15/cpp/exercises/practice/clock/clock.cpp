#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {

namespace {

// Normalize any integer number of minutes into the range [0, kDayMinutes-1].
inline int normalize(int total_minutes) {
    const int m = total_minutes % Clock::kDayMinutes;
    return m < 0 ? m + Clock::kDayMinutes : m;
}

}  // namespace

Clock::Clock(int hour, int minute)
    : minutes_(normalize(hour * 60 + minute)) {}

Clock& Clock::plus(int minutes) {
    minutes_ = normalize(minutes_ + minutes);
    return *this;
}

std::string Clock::to_string() const {
    std::ostringstream out;
    const int hour   = minutes_ / 60;
    const int minute = minutes_ % 60;
    out << std::setw(2) << std::setfill('0') << hour << ':'
        << std::setw(2) << std::setfill('0') << minute;
    return out.str();
}

}  // namespace date_independent

