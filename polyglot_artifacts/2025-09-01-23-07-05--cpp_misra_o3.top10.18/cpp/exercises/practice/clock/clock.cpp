#include "clock.h"

#include <cstdint>
#include <iomanip>
#include <sstream>

namespace date_independent {

namespace
{
    constexpr std::int32_t minutes_per_hour = static_cast<std::int32_t>(60);
    constexpr std::int32_t minutes_per_day  =
        static_cast<std::int32_t>(24) * minutes_per_hour;

    /* Normalise an absolute number of minutes to the range 0-1439 */
    std::int32_t normalize(std::int32_t total_minutes)
    {
        return ((total_minutes % minutes_per_day) + minutes_per_day) %
               minutes_per_day;
    }
} // unnamed namespace

clock clock::at(std::int32_t hour, std::int32_t minute)
{
    const std::int32_t total =
        normalize((hour * minutes_per_hour) + minute);
    return clock{total};
}

clock::clock(std::int32_t total_minutes)
    : m_total_minutes(normalize(total_minutes))
{
}

clock clock::plus(std::int32_t minute_delta) const
{
    const std::int32_t total =
        normalize(m_total_minutes + minute_delta);
    return clock{total};
}

clock clock::minus(std::int32_t minute_delta) const
{
    return plus(static_cast<std::int32_t>(-minute_delta));
}

bool operator==(const clock &lhs, const clock &rhs)
{
    return lhs.m_total_minutes == rhs.m_total_minutes;
}

bool operator!=(const clock &lhs, const clock &rhs)
{
    return !(lhs == rhs);
}

clock::operator std::string() const
{
    std::ostringstream oss;

    const std::int32_t hour   = m_total_minutes / minutes_per_hour;
    const std::int32_t minute = m_total_minutes % minutes_per_hour;

    oss << std::setfill('0') << std::setw(2) << hour << ':'
        << std::setfill('0') << std::setw(2) << minute;

    return oss.str();
}

}  // namespace date_independent
