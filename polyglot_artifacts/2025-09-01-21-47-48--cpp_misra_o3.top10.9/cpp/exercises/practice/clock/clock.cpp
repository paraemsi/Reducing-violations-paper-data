#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

namespace
{
    /* Minutes contained in one day                                    */
    constexpr std::int32_t minutesPerDay =
        static_cast<std::int32_t>(24) * static_cast<std::int32_t>(60);
}

/* ------------------------------------------------------------------ */
/* Utility that keeps the minute count within a single day            */
std::int32_t Clock::normalize(std::int32_t minutes)
{
    std::int32_t result = (minutes % minutesPerDay);

    if((result < static_cast<std::int32_t>(0)))
    {
        result += minutesPerDay;
    }

    return result;
}

/* Private ctor                                                       */
Clock::Clock(std::int32_t totalMinutes) : m_totalMinutes(normalize(totalMinutes))
{
}

/* ------------------------------------------------------------------ */
Clock Clock::at(std::int32_t hour, std::int32_t minute)
{
    const std::int32_t total =
        (hour * static_cast<std::int32_t>(60)) + minute;

    return Clock(total);
}

Clock Clock::plus(std::int32_t minutes) const
{
    return Clock(m_totalMinutes + minutes);
}

Clock Clock::minus(std::int32_t minutes) const
{
    return Clock(m_totalMinutes - minutes);
}

std::string Clock::to_string() const
{
    std::ostringstream oss;

    const std::int32_t hour   = m_totalMinutes / static_cast<std::int32_t>(60);
    const std::int32_t minute = m_totalMinutes % static_cast<std::int32_t>(60);

    oss << std::setfill('0') << std::setw(2) << hour
        << ':' << std::setw(2) << minute;

    return oss.str();
}

/* ------------------------------------------------------------------ */
/* Equality operators                                                 */
bool operator==(const Clock& lhs, const Clock& rhs)
{
    return (lhs.m_totalMinutes == rhs.m_totalMinutes);
}

bool operator!=(const Clock& lhs, const Clock& rhs)
{
    return !(lhs == rhs);
}

/* ------------------------------------------------------------------ */
/* Implicit conversion to std::string                                  */
std::string Clock::operator std::string() const
{
    return to_string();
}

}  // namespace date_independent
