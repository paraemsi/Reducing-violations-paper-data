#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {

namespace
{
/* Normalise minutes to the range 0-1439 inclusive */
static std::int32_t normalise(std::int32_t total_minutes) noexcept
{
    const std::int32_t minutes_per_day = (24 * 60);
    std::int32_t result = total_minutes % minutes_per_day;
    if((result < static_cast<std::int32_t>(0)))
    {
        result += minutes_per_day;
    }
    return result;
}
} // unnamed namespace

Clock Clock::at(std::int32_t hour, std::int32_t minute) noexcept
{
    return Clock(normalise(((hour * static_cast<std::int32_t>(60)) + minute)));
}

Clock Clock::plus(std::int32_t minutes) const noexcept
{
    return Clock(normalise(m_total_minutes + minutes));
}

Clock Clock::minus(std::int32_t minutes) const noexcept
{
    return Clock(normalise(m_total_minutes - minutes));
}

std::string Clock::to_string() const
{
    std::ostringstream oss;
    std::int32_t hour = (m_total_minutes / static_cast<std::int32_t>(60));
    std::int32_t minute = (m_total_minutes % static_cast<std::int32_t>(60));
    oss << std::setfill('0') << std::setw(2) << hour << ':' << std::setfill('0') << std::setw(2) << minute;
    return oss.str();
}

bool Clock::operator==(const Clock& other) const noexcept
{
    return (m_total_minutes == other.m_total_minutes);
}

bool Clock::operator!=(const Clock& other) const noexcept
{
    return (m_total_minutes != other.m_total_minutes);
}

Clock::Clock(std::int32_t total_minutes) noexcept :
    m_total_minutes(normalise(total_minutes))
{
}

}  // namespace date_independent
