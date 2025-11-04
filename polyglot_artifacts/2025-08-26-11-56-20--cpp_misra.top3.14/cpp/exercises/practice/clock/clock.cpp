#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(hour_t hour, minute_t minute)
    : m_hour(hour), m_minute(minute)
{
    normalize(m_hour, m_minute);
}

clock clock::at(hour_t hour, minute_t minute)
{
    return clock(hour, minute);
}

clock clock::plus(minute_t minutes) const
{
    hour_t hour = m_hour;
    minute_t minute = (m_minute + minutes);
    normalize(hour, minute);
    return clock(hour, minute);
}

clock clock::minus(minute_t minutes) const
{
    hour_t hour = m_hour;
    minute_t minute = (m_minute - minutes);
    normalize(hour, minute);
    return clock(hour, minute);
}

std::string clock::to_string() const
{
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << m_hour << ":"
        << std::setfill('0') << std::setw(2) << m_minute;
    return oss.str();
}

bool clock::operator==(const clock& other) const
{
    return ((m_hour == other.m_hour) && (m_minute == other.m_minute));
}

bool clock::operator!=(const clock& other) const
{
    return !((*this) == other);
}

void clock::normalize(hour_t& hour, minute_t& minute)
{
    // Normalize minutes
    hour = (hour + (minute / 60));
    minute = (minute % 60);
    if (minute < 0) {
        minute = (minute + 60);
        hour = (hour - 1);
    }
    // Normalize hours
    hour = (hour % 24);
    if (hour < 0) {
        hour = (hour + 24);
    }
}

}  // namespace date_independent
