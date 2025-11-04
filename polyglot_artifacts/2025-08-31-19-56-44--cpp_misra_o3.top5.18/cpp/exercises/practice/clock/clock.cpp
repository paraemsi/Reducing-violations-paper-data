#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

static constexpr std::int32_t minutes_in_hour = static_cast<std::int32_t>(60);
static constexpr std::int32_t minutes_in_day  = static_cast<std::int32_t>(24 * 60);

clock::clock(std::int32_t total_minutes)
    : m_total_minutes(normalize(total_minutes))
{
}

std::int32_t clock::normalize(std::int32_t total_minutes)
{
    /* Ensure value resides in the range [0, minutes_in_day).          */
    const std::int32_t mod = static_cast<std::int32_t>(
        (total_minutes % minutes_in_day + minutes_in_day) % minutes_in_day);
    return mod;
}

clock clock::at(std::int32_t hour, std::int32_t minute)
{
    const std::int32_t total = (hour * minutes_in_hour) + minute;
    return clock(total);
}

clock clock::plus(std::int32_t minutes) const
{
    return clock(m_total_minutes + minutes);
}

clock clock::minus(std::int32_t minutes) const
{
    return clock(m_total_minutes - minutes);
}

std::string clock::to_string() const
{
    const std::int32_t hour   = m_total_minutes / minutes_in_hour;
    const std::int32_t minute = m_total_minutes % minutes_in_hour;

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hour
        << ':' << std::setw(2) << std::setfill('0') << minute;
    return oss.str();
}

clock::operator std::string() const
{
    return to_string();
}

bool operator==(const clock& lhs, const clock& rhs)
{
    return (lhs.m_total_minutes == rhs.m_total_minutes);
}

bool operator!=(const clock& lhs, const clock& rhs)
{
    return (lhs.m_total_minutes != rhs.m_total_minutes);
}

}  // namespace date_independent
