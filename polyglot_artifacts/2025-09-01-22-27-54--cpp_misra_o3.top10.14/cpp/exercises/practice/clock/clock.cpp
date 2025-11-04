#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

// ---------- private helpers -------------------------------------------------
std::int32_t Clock::normalise(std::int32_t minutes)
{
    // Ensure result is within [0, MinutesPerDay)
    const std::int32_t modded =
        ((minutes % MinutesPerDay) + MinutesPerDay) % MinutesPerDay;
    return modded;
}

// ---------- constructors / factories ---------------------------------------
Clock::Clock(std::int32_t minutes_from_midnight)
    : m_minutes{normalise(minutes_from_midnight)}
{
}

Clock Clock::at(std::int32_t hour, std::int32_t minute)
{
    // Convert to total minutes and delegate to private ctor
    const std::int32_t total =
        ((hour * MinutesPerHour) + minute);
    return Clock{total};
}

// ---------- public API ------------------------------------------------------
Clock Clock::add_minutes(std::int32_t minutes) const
{
    const std::int32_t new_total = (m_minutes + minutes);
    return Clock{new_total};
}

std::string Clock::to_string() const
{
    const std::int32_t hour   = m_minutes / MinutesPerHour;
    const std::int32_t minute = m_minutes % MinutesPerHour;

    std::ostringstream oss;
    oss << std::setfill('0')
        << std::setw(2) << hour
        << ':'
        << std::setw(2) << minute;
    return oss.str();
}

Clock Clock::plus(std::int32_t minutes) const
{
    return add_minutes(minutes);
}

Clock Clock::minus(std::int32_t minutes) const
{
    return add_minutes(-minutes);
}

Clock::operator std::string() const
{
    return to_string();
}

// ---------- non-member operators -------------------------------------------
bool operator==(const Clock& lhs, const Clock& rhs)
{
    return lhs.m_minutes == rhs.m_minutes;
}

bool operator!=(const Clock& lhs, const Clock& rhs)
{
    return !(lhs == rhs);
}

}  // namespace date_independent
