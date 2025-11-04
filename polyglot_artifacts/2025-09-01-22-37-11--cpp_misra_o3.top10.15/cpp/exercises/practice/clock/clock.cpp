#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

namespace {

constexpr date_independent::clock::minutes_t MINUTES_PER_HOUR =
    static_cast<date_independent::clock::minutes_t>(60);
constexpr date_independent::clock::minutes_t MINUTES_PER_DAY =
    static_cast<date_independent::clock::minutes_t>(24) * MINUTES_PER_HOUR;

} // unnamed namespace

clock::clock(minutes_t total_minutes) : m_total_minutes(normalize(total_minutes))
{
}

clock clock::at(minutes_t hour, minutes_t minute)
{
    return clock((hour * MINUTES_PER_HOUR) + minute);
}

clock clock::plus(minutes_t minute) const
{
    return clock((m_total_minutes + minute));
}

clock clock::minus(minutes_t minute) const
{
    return clock((m_total_minutes - minute));
}

std::string clock::to_string() const
{
    minutes_t hour = m_total_minutes / MINUTES_PER_HOUR;
    minutes_t minute = m_total_minutes % MINUTES_PER_HOUR;

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hour << ':' << std::setw(2) << minute;
    return oss.str();
}

clock::operator std::string() const
{
    return to_string();
}

clock::minutes_t clock::normalize(minutes_t total_minutes)
{
    minutes_t result = total_minutes % MINUTES_PER_DAY;
    if (result < static_cast<minutes_t>(0))
    {
        result += MINUTES_PER_DAY;
    }
    return result;
}

bool operator==(const clock& lhs, const clock& rhs)
{
    return lhs.m_total_minutes == rhs.m_total_minutes;
}

bool operator!=(const clock& lhs, const clock& rhs)
{
    return !(lhs == rhs);
}

}  // namespace date_independent
