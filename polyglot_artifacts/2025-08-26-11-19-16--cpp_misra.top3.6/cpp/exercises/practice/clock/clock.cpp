#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {

Clock::Clock(hour_t hour, minute_t minute)
    : m_hour(hour), m_minute(minute)
{
    normalize();
}

void Clock::normalize()
{
    // Convert everything to minutes, then back to hour/minute
    minute_t total_minutes = (static_cast<minute_t>(m_hour) * MINUTES_PER_HOUR) + m_minute;

    // Ensure positive modulo for negative times
    total_minutes = static_cast<minute_t>(
        (total_minutes % MINUTES_PER_DAY + MINUTES_PER_DAY) % MINUTES_PER_DAY
    );

    m_hour = static_cast<hour_t>(total_minutes / MINUTES_PER_HOUR);
    m_minute = static_cast<minute_t>(total_minutes % MINUTES_PER_HOUR);
}

Clock Clock::add_minutes(minute_t minutes) const
{
    return Clock(m_hour, static_cast<minute_t>(m_minute + minutes));
}

Clock Clock::subtract_minutes(minute_t minutes) const
{
    return add_minutes(static_cast<minute_t>(-minutes));
}

std::string Clock::to_string() const
{
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << static_cast<int>(m_hour)
        << ":" << std::setfill('0') << std::setw(2) << static_cast<int>(m_minute);
    return oss.str();
}

bool Clock::operator==(const Clock& other) const
{
    return ((m_hour == other.m_hour) && (m_minute == other.m_minute));
}

bool Clock::operator!=(const Clock& other) const
{
    return !((*this) == other);
}

namespace clock {
    Clock at(hour_t hour, minute_t minute) {
        return Clock(hour, minute);
    }
}

}  // namespace date_independent
