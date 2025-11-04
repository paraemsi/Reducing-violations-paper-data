#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(std::int32_t totalMinutes) noexcept
    : m_minutes(normalize(totalMinutes))
{
}

std::int32_t clock::normalize(std::int32_t minutes) noexcept
{
    std::int32_t result = (minutes % clock::MINUTES_PER_DAY);
    if((result) < static_cast<std::int32_t>(0))
    {
        result += clock::MINUTES_PER_DAY;
    }
    return result;
}

clock clock::at(std::int32_t hour, std::int32_t minute)
{
    const std::int32_t total =
        (hour * clock::MINUTES_PER_HOUR) + minute;
    return clock(total);
}

clock clock::plus(std::int32_t minutes) const
{
    return clock(normalize(m_minutes + minutes));
}

clock clock::minus(std::int32_t minutes) const
{
    return plus(-minutes);
}

std::string clock::to_string() const
{
    const std::int32_t hours = (m_minutes / clock::MINUTES_PER_HOUR);
    const std::int32_t minutes = (m_minutes % clock::MINUTES_PER_HOUR);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hours
        << ':' << std::setw(2) << minutes;
    return oss.str();
}

clock::operator std::string() const
{
    return to_string();
}

bool operator==(const clock& lhs, const clock& rhs) noexcept
{
    return (lhs.m_minutes == rhs.m_minutes);
}

bool operator!=(const clock& lhs, const clock& rhs) noexcept
{
    return (lhs.m_minutes != rhs.m_minutes);
}

} // namespace date_independent
