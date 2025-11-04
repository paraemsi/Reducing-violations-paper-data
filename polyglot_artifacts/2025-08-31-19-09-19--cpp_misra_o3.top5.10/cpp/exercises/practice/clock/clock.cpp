#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

Clock::Clock(const std::int32_t totalMinutes) noexcept : minutes_{wrap(totalMinutes)} { }

Clock Clock::at(const std::int32_t hour, const std::int32_t minute) noexcept
{
    const std::int32_t totalMinutes{(hour * static_cast<std::int32_t>(60)) + minute};
    return Clock{totalMinutes};
}

Clock Clock::plus(const std::int32_t minutes) const noexcept
{
    return Clock{wrap(minutes_ + minutes)};
}

Clock Clock::minus(const std::int32_t minutes) const noexcept
{
    return Clock{wrap(minutes_ - minutes)};
}

std::string Clock::to_string() const
{
    std::ostringstream oss{};

    const std::int32_t hours{minutes_ / static_cast<std::int32_t>(60)};
    const std::int32_t mins{minutes_ % static_cast<std::int32_t>(60)};

    oss << std::setfill('0') << std::setw(2) << hours
        << ':' << std::setfill('0') << std::setw(2) << mins;

    return oss.str();
}

bool operator==(const Clock &lhs, const Clock &rhs) noexcept
{
    return (lhs.minutes_ == rhs.minutes_);
}

std::int32_t Clock::wrap(const std::int32_t minutes) noexcept
{
    std::int32_t wrapped{minutes % minutes_per_day};
    if (wrapped < static_cast<std::int32_t>(0)) { wrapped += minutes_per_day; }
    return wrapped;
}

}  // namespace date_independent
