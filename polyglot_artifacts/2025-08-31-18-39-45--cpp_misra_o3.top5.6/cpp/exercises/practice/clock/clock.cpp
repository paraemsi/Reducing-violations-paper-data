#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

namespace
{
    // Number of minutes in one day: 24 * 60
    constexpr std::int32_t minutes_per_day =
        static_cast<std::int32_t>(24) * static_cast<std::int32_t>(60);
}

Clock Clock::at(std::int32_t hour, std::int32_t minute)
{
    // Allow hours or minutes outside their usual range – wrap later.
    std::int32_t total =
        ((hour * static_cast<std::int32_t>(60)) + minute);
    return Clock{wrap(total)};
}

Clock Clock::plus(std::int32_t minute_delta) const
{
    std::int32_t total = wrap((m_total_minutes + minute_delta));
    return Clock{total};
}

Clock Clock::minus(std::int32_t minute_delta) const
{
    // Delegate to plus() with the negated offset.
    return plus(-minute_delta);
}

Clock::operator std::string() const
{
    return to_string();
}

std::string Clock::to_string() const
{
    std::ostringstream oss;
    oss << std::setfill('0')
        << std::setw(2) << (m_total_minutes / static_cast<std::int32_t>(60))
        << ':'
        << std::setfill('0')
        << std::setw(2) << (m_total_minutes % static_cast<std::int32_t>(60));
    return oss.str();
}

bool operator==(const Clock& lhs, const Clock& rhs)
{
    return (lhs.m_total_minutes == rhs.m_total_minutes);
}

bool operator!=(const Clock& lhs, const Clock& rhs)
{
    return (lhs.m_total_minutes != rhs.m_total_minutes);
}

Clock::Clock(std::int32_t total_minutes) :
    m_total_minutes{wrap(total_minutes)}
{
    // Body intentionally left empty
}

std::int32_t Clock::wrap(std::int32_t minutes)
{
    // Normalise into the 0-to-1439 range using modulo arithmetic.
    std::int32_t result = (minutes % minutes_per_day);
    if(result < static_cast<std::int32_t>(0))
    {
        result = (result + minutes_per_day);
    }
    return result;
}

}  // namespace date_independent
