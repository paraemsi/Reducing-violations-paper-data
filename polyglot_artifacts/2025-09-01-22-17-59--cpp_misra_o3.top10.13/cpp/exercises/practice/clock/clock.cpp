#include "clock.h"
#include <sstream>
#include <iomanip>

namespace date_independent {

static constexpr std::int32_t minutes_per_hour { static_cast<std::int32_t>(60) };
static constexpr std::int32_t minutes_per_day  { static_cast<std::int32_t>(24) * minutes_per_hour };

clock clock::at(std::int32_t hour, std::int32_t minute)
{
    const std::int32_t total_minutes { (hour * minutes_per_hour) + minute };
    return clock{ total_minutes };
}

clock clock::add_minutes(std::int32_t minutes) const
{
    return clock{ m_total_minutes + minutes };
}

clock clock::subtract_minutes(std::int32_t minutes) const
{
    return clock{ m_total_minutes - minutes };
}

std::string clock::to_string() const
{
    const std::int32_t hour   { m_total_minutes / minutes_per_hour };
    const std::int32_t minute { m_total_minutes % minutes_per_hour };

    std::ostringstream oss {};
    oss << std::setfill('0')
        << std::setw(2) << hour
        << ':'
        << std::setw(2) << minute;
    return oss.str();
}

bool operator==(const clock& lhs, const clock& rhs)
{
    return (lhs.m_total_minutes == rhs.m_total_minutes);
}

bool operator!=(const clock& lhs, const clock& rhs)
{
    return !(lhs == rhs);
}

clock::clock(std::int32_t total_minutes)
    : m_total_minutes { ( ( (total_minutes % minutes_per_day) + minutes_per_day ) % minutes_per_day ) }
{
    /* m_total_minutes is now within the valid range [0, 1439]. */
}

}  // namespace date_independent
