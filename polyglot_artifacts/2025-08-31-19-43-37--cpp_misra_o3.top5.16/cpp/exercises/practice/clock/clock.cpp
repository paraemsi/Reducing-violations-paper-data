#include "clock.h"

#include <iomanip>
#include <sstream>
#include <cstdint>
#include <ostream>
#include <string>

namespace date_independent {

Clock::Clock(std::int16_t total_minutes) noexcept
    : m_minutes_since_midnight(total_minutes)
{
}

std::int16_t Clock::normalize(std::int32_t minute) noexcept
{
    const std::int32_t minutes_per_day =
        static_cast<std::int32_t>(k_minutes_per_day);

    std::int32_t result = minute % minutes_per_day;
    if(result < static_cast<std::int32_t>(0))
    {
        result += minutes_per_day;
    }
    return static_cast<std::int16_t>(result);
}

Clock Clock::at(std::int16_t hour, std::int16_t minute) noexcept
{
    const std::int32_t total = (static_cast<std::int32_t>(hour) *
                                static_cast<std::int32_t>(60))
                             + static_cast<std::int32_t>(minute);
    return Clock(normalize(total));
}

Clock Clock::plus(std::int16_t minute) const noexcept
{
    const std::int32_t total = static_cast<std::int32_t>(m_minutes_since_midnight)
                             + static_cast<std::int32_t>(minute);
    return Clock(normalize(total));
}

Clock Clock::minus(std::int16_t minute) const noexcept
{
    const std::int32_t total = static_cast<std::int32_t>(m_minutes_since_midnight)
                             - static_cast<std::int32_t>(minute);
    return Clock(normalize(total));
}

bool operator==(const Clock& lhs, const Clock& rhs) noexcept
{
    return lhs.m_minutes_since_midnight == rhs.m_minutes_since_midnight;
}

std::string Clock::to_string() const
{
    const std::int16_t hour =
        static_cast<std::int16_t>(m_minutes_since_midnight /
                                  static_cast<std::int16_t>(60));
    const std::int16_t minute =
        static_cast<std::int16_t>(m_minutes_since_midnight %
                                  static_cast<std::int16_t>(60));

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2)
        << static_cast<std::int32_t>(hour)
        << ':' << std::setfill('0') << std::setw(2)
        << static_cast<std::int32_t>(minute);
    return oss.str();
}

Clock::operator std::string() const
{
    return to_string();
}

bool operator!=(const Clock& lhs, const Clock& rhs) noexcept
{
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Clock& clock)
{
    os << clock.to_string();
    return os;
}

Clock operator+(const Clock& clock, std::int16_t minute) noexcept
{
    return clock.plus(minute);
}

Clock operator-(const Clock& clock, std::int16_t minute) noexcept
{
    return clock.minus(minute);
}

}  // namespace date_independent
