#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

namespace clock {

namespace {
    constexpr std::int32_t minutes_per_hour = std::int32_t{60};
    constexpr std::int32_t minutes_per_day = (std::int32_t{24} * std::int32_t{60});

    constexpr std::int32_t normalize_total(const std::int32_t total) noexcept
    {
        std::int32_t m = (total % minutes_per_day);
        if ((m < std::int32_t{0})) {
            m = (m + minutes_per_day);
        }
        return m;
    }
}  // unnamed namespace

Clock::Clock(const std::int32_t hour, const std::int32_t minute) noexcept
    : minutes_since_midnight{ normalize_total(((hour * minutes_per_hour) + minute)) }
{
}

Clock Clock::plus_minutes(const std::int32_t minutes) const noexcept
{
    const std::int32_t new_total = (minutes_since_midnight + minutes);
    return Clock{ std::int32_t{0}, new_total };
}

Clock Clock::plus(const std::int32_t minutes) const noexcept
{
    return plus_minutes(minutes);
}

std::int32_t Clock::total_minutes() const noexcept
{
    return minutes_since_midnight;
}

std::string Clock::to_string() const
{
    const std::int32_t hours = (minutes_since_midnight / minutes_per_hour);
    const std::int32_t mins = (minutes_since_midnight % minutes_per_hour);

    std::ostringstream os;
    os << std::setw(2);
    os << std::setfill('0');
    os << hours;
    os << ':';
    os << std::setw(2);
    os << std::setfill('0');
    os << mins;
    return os.str();
}

Clock::operator std::string() const
{
    return to_string();
}

bool operator==(const Clock& lhs, const Clock& rhs) noexcept
{
    return (lhs.total_minutes() == rhs.total_minutes());
}

bool operator!=(const Clock& lhs, const Clock& rhs) noexcept
{
    return (lhs.total_minutes() != rhs.total_minutes());
}

Clock at(const std::int32_t hour, const std::int32_t minute) noexcept
{
    return Clock{ hour, minute };
}

}  // namespace clock

}  // namespace date_independent
