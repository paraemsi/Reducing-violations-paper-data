#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

Clock::Clock(hour_t hour, minute_t minute)
    : m_hour(hour), m_minute(minute)
{
    normalize(m_hour, m_minute);
}

Clock Clock::plus(minute_t minutes) const
{
    hour_t hour = m_hour;
    minute_t minute = (m_minute + minutes);
    normalize(hour, minute);
    return Clock(hour, minute);
}

Clock Clock::minus(minute_t minutes) const
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
    minute_t norm_minutes = (total_minutes % MINUTES_PER_DAY);
    if (norm_minutes < 0) {
        norm_minutes = (norm_minutes + MINUTES_PER_DAY);
    }

    hour = (norm_minutes / MINUTES_PER_HOUR);
    minute = (norm_minutes % MINUTES_PER_HOUR);
}

Clock clock::at(hour_t hour, minute_t minute)
{
    return Clock(hour, minute);
}

}  // namespace date_independent
