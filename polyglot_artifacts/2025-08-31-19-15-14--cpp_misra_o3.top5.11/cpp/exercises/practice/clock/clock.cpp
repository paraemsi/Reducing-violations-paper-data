#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {

namespace
{
    constexpr Clock::minutes_t minutes_per_hour = static_cast<Clock::minutes_t>(60);
    constexpr Clock::minutes_t minutes_per_day  = static_cast<Clock::minutes_t>(24 * 60);

    auto normalize(Clock::minutes_t total_minutes) -> Clock::minutes_t
    {
        total_minutes = (total_minutes % minutes_per_day);
        if (total_minutes < static_cast<Clock::minutes_t>(0))
        {
            total_minutes += minutes_per_day;
        }
        return total_minutes;
    }
} // unnamed namespace

Clock::Clock(minutes_t total_minutes) : m_minutes(normalize(total_minutes))
{
}

auto Clock::at(minutes_t hour, minutes_t minute) -> Clock
{
    minutes_t total_minutes = ((hour * minutes_per_hour) + minute);
    return Clock { total_minutes };
}

auto Clock::plus(minutes_t minutes) const -> Clock
{
    minutes_t total = (m_minutes + minutes);
    return Clock { total };
}

auto Clock::minus(minutes_t minutes) const -> Clock
{
    minutes_t total = (m_minutes - minutes);
    return Clock { total };
}

auto Clock::operator==(const Clock& other) const -> bool
{
    return (m_minutes == other.m_minutes);
}

auto Clock::to_string() const -> std::string
{
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << (m_minutes / minutes_per_hour)
        << ':' << std::setfill('0') << std::setw(2) << (m_minutes % minutes_per_hour);
    return oss.str();
}

Clock::operator std::string() const
{
    return to_string();
}

}  // namespace date_independent
