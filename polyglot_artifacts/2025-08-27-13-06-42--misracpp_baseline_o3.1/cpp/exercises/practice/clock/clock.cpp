#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {

int Clock::normalize(int minutes) {
    constexpr int kMinutesPerDay = 24 * 60;
    int mod = minutes % kMinutesPerDay;
    if (mod < 0) {
        mod += kMinutesPerDay;
    }
    return mod;
}

Clock::Clock(int hour, int minute /*= 0*/)
    : minute_of_day_(normalize(hour * 60 + minute)) {}

Clock Clock::plus(int minutes) const {
    return Clock(0, minute_of_day_ + minutes);
}

Clock Clock::minus(int minutes) const {
    return plus(-minutes);
}

std::string Clock::to_string() const {
    int hour = minute_of_day_ / 60;
    int minute = minute_of_day_ % 60;
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hour << ':'
        << std::setw(2) << std::setfill('0') << minute;
    return oss.str();
}

bool Clock::operator==(const Clock& other) const {
    return minute_of_day_ == other.minute_of_day_;
}

}  // namespace date_independent
