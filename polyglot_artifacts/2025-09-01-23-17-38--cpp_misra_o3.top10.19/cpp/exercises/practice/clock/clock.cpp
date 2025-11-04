#include "clock.h"

#include <sstream>
#include <iomanip>

namespace date_independent {

namespace
{
    constexpr std::int32_t minutes_per_day  = static_cast<std::int32_t>(24) * static_cast<std::int32_t>(60);
    constexpr std::int32_t minutes_per_hour = static_cast<std::int32_t>(60);

    constexpr std::int32_t normalise(std::int32_t total_minutes) noexcept
    {
        std::int32_t result = total_minutes % minutes_per_day;
        if (result < static_cast<std::int32_t>(0))
        {
            result += minutes_per_day;
        }
        return result;
    }
}  // unnamed namespace

Clock Clock::at(std::int32_t hour, std::int32_t minute) noexcept
{
    const std::int32_t total = ((hour * minutes_per_hour) + minute);
    return Clock{normalise(total)};
}

Clock::Clock(std::int32_t total_minutes) noexcept
    : m_total_minutes(normalise(total_minutes))
{
}

Clock Clock::add_minutes(std::int32_t minutes) const noexcept
{
    return Clock{normalise(m_total_minutes + minutes)};
}

Clock Clock::plus(std::int32_t minutes) const noexcept
{
    return add_minutes(minutes);
}

Clock Clock::minus(std::int32_t minutes) const noexcept
{
    return add_minutes(-minutes);
}

Clock& Clock::operator+=(std::int32_t minutes) noexcept
{
    m_total_minutes = normalise(m_total_minutes + minutes);
    return *this;
}

Clock& Clock::operator-=(std::int32_t minutes) noexcept
{
    m_total_minutes = normalise(m_total_minutes - minutes);
    return *this;
}

std::string Clock::to_string() const
{
    const std::int32_t hour   = (m_total_minutes / minutes_per_hour);
    const std::int32_t minute = (m_total_minutes % minutes_per_hour);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hour << ':' << std::setw(2) << minute;
    return oss.str();
}

bool operator==(const Clock& lhs, const Clock& rhs) noexcept
{
    return (lhs.m_total_minutes == rhs.m_total_minutes);
}

bool operator!=(const Clock& lhs, const Clock& rhs) noexcept
{
    return !(lhs == rhs);
}

Clock operator+(Clock lhs, std::int32_t minutes) noexcept
{
    lhs += minutes;
    return lhs;
}

Clock operator-(Clock lhs, std::int32_t minutes) noexcept
{
    lhs += (-minutes);
    return lhs;
}

}  // namespace date_independent
