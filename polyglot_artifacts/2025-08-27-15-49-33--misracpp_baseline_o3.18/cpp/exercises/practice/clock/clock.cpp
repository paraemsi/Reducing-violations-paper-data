#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

int Clock::normalise(int total_minutes) {
    const int MINUTES_PER_DAY = 24 * 60;
    // handle negative values correctly
    total_minutes %= MINUTES_PER_DAY;
    if (total_minutes < 0)
        total_minutes += MINUTES_PER_DAY;
    return total_minutes;
}

Clock::Clock(int total_minutes)
    : minutes_from_midnight_{normalise(total_minutes)} {}

Clock Clock::at(int hour, int minute) {
    return Clock(hour * 60 + minute);
}

Clock Clock::plus(int minutes) const {
    return Clock(minutes_from_midnight_ + minutes);
}

Clock Clock::minus(int minutes) const {
    return Clock(minutes_from_midnight_ - minutes);
}

std::string Clock::to_string() const {
    std::ostringstream oss;
    int hours = minutes_from_midnight_ / 60;
    int minutes = minutes_from_midnight_ % 60;
    oss << std::setfill('0') << std::setw(2) << hours << ':'
        << std::setfill('0') << std::setw(2) << minutes;
    return oss.str();
}

bool Clock::operator==(const Clock &other) const {
    return minutes_from_midnight_ == other.minutes_from_midnight_;
}

}  // namespace date_independent
