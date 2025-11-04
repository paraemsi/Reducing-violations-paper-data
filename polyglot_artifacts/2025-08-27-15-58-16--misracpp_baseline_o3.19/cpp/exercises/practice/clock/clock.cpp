#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {
namespace clock {

int Clock::normalize(int minutes) {
    const int kDayMinutes = 24 * 60;
    int mod = minutes % kDayMinutes;
    if (mod < 0) {
        mod += kDayMinutes;
    }
    return mod;
}

Clock::Clock(int total_minutes) : minutes_(normalize(total_minutes)) {}

Clock at(int hour, int minute) {
    return Clock(hour * 60 + minute);
}

Clock Clock::plus(int minutes) const {
    return Clock(minutes_ + minutes);
}

Clock Clock::minus(int minutes) const {
    return Clock(minutes_ - minutes);
}

std::string Clock::to_string() const {
    int hours = minutes_ / 60;
    int mins  = minutes_ % 60;
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours << ':'
        << std::setw(2) << std::setfill('0') << mins;
    return oss.str();
}

bool Clock::operator==(const Clock& other) const {
    return minutes_ == other.minutes_;
}

}  // namespace clock
}  // namespace date_independent
