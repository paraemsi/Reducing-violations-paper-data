#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(hour_t hour, minute_t minute)
    : m_hour(0), m_minute(0)
{
    minute_t total_minutes = (hour * minutes_per_hour) + minute;
    minute_t norm = normalize_minutes(total_minutes);
    m_hour = (norm / minutes_per_hour);
    m_minute = (norm % minutes_per_hour);
}

clock clock::at(hour_t hour, minute_t minute)
{
    return clock(hour, minute);
}

clock clock::add_minutes(minute_t minutes) const
{
    minute_t total_minutes = ((m_hour * minutes_per_hour) + m_minute) + minutes;
    minute_t norm = normalize_minutes(total_minutes);
    hour_t new_hour = (norm / minutes_per_hour);
    minute_t new_minute = (norm % minutes_per_hour);
    return clock(new_hour, new_minute);
}

clock clock::plus(minute_t minutes) const
{
    return add_minutes(minutes);
}

clock clock::subtract_minutes(minute_t minutes) const
{
    minute_t total_minutes = ((m_hour * minutes_per_hour) + m_minute) - minutes;
    minute_t norm = normalize_minutes(total_minutes);
    hour_t new_hour = (norm / minutes_per_hour);
    minute_t new_minute = (norm % minutes_per_hour);
    return clock(new_hour, new_minute);
}

clock clock::minus(minute_t minutes) const
{
    return subtract_minutes(minutes);
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

clock::minute_t clock::normalize_minutes(minute_t minutes)
{
    minute_t result = minutes % minutes_per_day;
    if(result < static_cast<minute_t>(0))
    {
        result = (result + minutes_per_day);
    }
    return result;
}

}  // namespace date_independent
