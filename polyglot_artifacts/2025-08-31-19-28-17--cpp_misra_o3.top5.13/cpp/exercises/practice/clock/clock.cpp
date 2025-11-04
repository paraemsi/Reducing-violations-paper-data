#include "clock.h"

#include <iomanip>
#include <sstream>
#include <ostream>

namespace date_independent {

Clock::Clock(minutes_t minutes_since_midnight) noexcept
    : minutes_since_midnight_{ normalise(minutes_since_midnight) }
{
}

minutes_t Clock::normalise(minutes_t minutes) noexcept
{
    // ensure value lies in [0, minutes_per_day_ - 1]
    const minutes_t mod { (minutes % minutes_per_day_) };
    // adding minutes_per_day_ before the second modulo guarantees
    // a non-negative result even when the first modulo is negative
    return (mod + minutes_per_day_) % minutes_per_day_;
}

Clock Clock::at(minutes_t hour, minutes_t minute) noexcept
{
    const minutes_t total_minutes { (hour * static_cast<minutes_t>(60)) + minute };
    return Clock{ total_minutes };
}

Clock Clock::plus(minutes_t minute_delta) const noexcept
{
    return Clock{ minutes_since_midnight_ + minute_delta };
}

Clock Clock::minus(minutes_t minute_delta) const noexcept
{
    return Clock{ minutes_since_midnight_ - minute_delta };
}

std::string Clock::str() const
{
    const minutes_t hours { minutes_since_midnight_ / static_cast<minutes_t>(60) };
    const minutes_t minutes { minutes_since_midnight_ % static_cast<minutes_t>(60) };

    std::ostringstream oss {};
    oss << std::setfill('0') << std::setw(2) << hours
        << ':' << std::setw(2) << minutes;
    return oss.str();
}

bool operator==(const Clock& lhs, const Clock& rhs) noexcept
{
    return (lhs.minutes_since_midnight_ == rhs.minutes_since_midnight_);
}

bool operator!=(const Clock& lhs, const Clock& rhs) noexcept
{
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Clock& clk)
{
    os << clk.str();
    return os;
}

}  // namespace date_independent
