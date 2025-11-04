#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

constexpr std::int32_t Clock::kMinutesPerDay;

Clock Clock::at(std::int32_t hour, std::int32_t minute)
{
    const std::int32_t total_minutes =
        ((hour * static_cast<std::int32_t>(60)) + minute);

    return Clock(total_minutes);
}

Clock Clock::plus(std::int32_t minute_offset) const
{
    const std::int32_t new_total =
        (m_total_minutes + minute_offset);

    return Clock(new_total);
}

Clock Clock::minus(std::int32_t minute_offset) const
{
    const std::int32_t new_total =
        (m_total_minutes - minute_offset);

    return Clock(new_total);
}

std::string Clock::to_string() const
{
    const std::int32_t hours =
        (m_total_minutes / static_cast<std::int32_t>(60));
    const std::int32_t minutes =
        (m_total_minutes % static_cast<std::int32_t>(60));

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hours << ':'
        << std::setw(2) << minutes;
    return oss.str();
}

date_independent::Clock::operator std::string() const
{
    return to_string();
}

bool operator==(const Clock& lhs, const Clock& rhs)
{
    return (lhs.m_total_minutes == rhs.m_total_minutes);
}

bool operator!=(const Clock& lhs, const Clock& rhs)
{
    return !(lhs == rhs);
}

Clock::Clock(std::int32_t total_minutes) : m_total_minutes(total_minutes)
{
    normalize();
}

void Clock::normalize()
{
    m_total_minutes = (m_total_minutes % kMinutesPerDay); // Range now [-1439, 1439]

    if (m_total_minutes < static_cast<std::int32_t>(0))
    {
        m_total_minutes += kMinutesPerDay;
    }
}

}  // namespace date_independent
