#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {

namespace clock {

Clock::Clock(int hour, int minute) : hour_(hour), minute_(minute) {
    normalize();
}

Clock Clock::plus(int minutes) const {
    Clock result(hour_, minute_ + minutes);
    return result;
}

Clock Clock::minus(int minutes) const {
    Clock result(hour_, minute_ - minutes);
    return result;
}

std::string Clock::to_string() const {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hour_ << ":"
        << std::setw(2) << std::setfill('0') << minute_;
    return oss.str();
}

bool Clock::operator==(const Clock& other) const {
    return hour_ == other.hour_ && minute_ == other.minute_;
}

void Clock::normalize() {
    int total_minutes = hour_ * 60 + minute_;
    total_minutes = ((total_minutes % 1440) + 1440) % 1440; // wrap around 24h
    hour_ = total_minutes / 60;
    minute_ = total_minutes % 60;
}

} // namespace clock

}  // namespace date_independent
