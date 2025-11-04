#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

namespace
{
constexpr std::int32_t minutes_per_hour  = 60;
constexpr std::int32_t minutes_in_day    = (static_cast<std::int32_t>(24) * minutes_per_hour);

/* Normalise an (possibly negative) minute count to 0-1439 */
static std::int32_t normalise_minutes(std::int32_t total_minutes) noexcept
{
    std::int32_t result = (total_minutes % minutes_in_day);
    if (result < 0)
    {
        result += minutes_in_day;
    }
    return result;
}
} /* unnamed namespace */

clock clock::at(std::int32_t hour, std::int32_t minute) noexcept
{
    std::int32_t total = ((hour * minutes_per_hour) + minute);
    return clock{total};
}

clock::clock(std::int32_t total_minutes) noexcept
    : m_total_minutes{normalise_minutes(total_minutes)}
{
}

clock clock::plus(std::int32_t minutes) const noexcept
{
    std::int32_t new_total = (m_total_minutes + minutes);
    return clock{new_total};
}

std::string clock::to_string() const
{
    std::int32_t hour   = (m_total_minutes / minutes_per_hour);
    std::int32_t minute = (m_total_minutes % minutes_per_hour);

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hour
        << ':'
        << std::setw(2) << std::setfill('0') << minute;
    return oss.str();
}

bool operator==(const clock& lhs, const clock& rhs) noexcept
{
    return (lhs.m_total_minutes == rhs.m_total_minutes);
}

bool operator!=(const clock& lhs, const clock& rhs) noexcept
{
    return !(lhs == rhs);
}

}  // namespace date_independent
