#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {

Clock::Clock(hour_t hour, minute_t minute)
    : m_hour(hour), m_minute(minute)
{
    normalize(m_hour, m_minute);
}

Clock Clock::add_minutes(minute_t minutes) const
{
    hour_t hour = m_hour;
    minute_t minute = (m_minute + minutes);
    normalize(hour, minute);
    return Clock(hour, minute);
}

Clock Clock::subtract_minutes(minute_t minutes) const
{
    hour_t hour = m_hour;
    minute_t minute = (m_minute - minutes);
    normalize(hour, minute);
    return Clock(hour, minute);
}

std::string Clock::to_string() const
{
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << m_hour << ":"
        << std::setfill('0') << std::setw(2) << m_minute;
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

void Clock::normalize(hour_t& hour, minute_t& minute)
{
    minute_t total_minutes = (hour * MINUTES_PER_HOUR) + minute;
    // Ensure positive modulo for negative times
    total_minutes = ((total_minutes % MINUTES_PER_DAY) + MINUTES_PER_DAY) % MINUTES_PER_DAY;
    hour = (total_minutes / MINUTES_PER_HOUR);
    minute = (total_minutes % MINUTES_PER_HOUR);
}

namespace clock {
Clock at(hour_t hour, minute_t minute)
{
    return Clock(hour, minute);
}
} // namespace clock

}  // namespace date_independent
