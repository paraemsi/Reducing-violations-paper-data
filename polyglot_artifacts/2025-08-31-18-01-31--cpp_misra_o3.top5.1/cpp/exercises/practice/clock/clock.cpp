#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

Clock::Clock(hour_t hour, minute_t minute) noexcept
    : minutes_since_midnight_(normalize(((hour * static_cast<minute_t>(60)) + minute))) { }

Clock Clock::plus(minute_t minutes) const noexcept {
    return Clock{static_cast<hour_t>(0), static_cast<minute_t>((minutes_since_midnight_ + minutes))};
}

Clock Clock::minus(minute_t minutes) const noexcept {
    return plus(static_cast<minute_t>(-minutes));
}

std::string Clock::to_string() const {
    std::ostringstream os;
    minute_t adjusted_minutes = normalize(minutes_since_midnight_);
    minute_t hr   = static_cast<minute_t>(adjusted_minutes / static_cast<minute_t>(60));
    minute_t min  = static_cast<minute_t>(adjusted_minutes % static_cast<minute_t>(60));

    os << std::setfill('0') << std::setw(2) << hr << ':' << std::setw(2) << min;
    return os.str();
}

bool Clock::operator==(const Clock& other) const noexcept {
    return (minutes_since_midnight_ == other.minutes_since_midnight_);
}

bool Clock::operator!=(const Clock& other) const noexcept {
    return !(*this == other);
}

minute_t Clock::normalize(minute_t total_minutes) noexcept {
    constexpr minute_t mod = Clock::minutes_per_day_;
    minute_t result = static_cast<minute_t>(total_minutes % mod);

    if (result < static_cast<minute_t>(0)) {
        result = static_cast<minute_t>(result + mod);
    }

    return result;
}

std::string string(const Clock& clk) {
    return clk.to_string();
}

} // namespace date_independent
