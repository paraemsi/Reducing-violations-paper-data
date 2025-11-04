#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(minutes_t totalMinutes) : m_totalMinutes{totalMinutes}
{
    // Normalise into the range [0, minutes_per_day).
    while (m_totalMinutes < minutes_t{0})
    {
        m_totalMinutes += clock::minutes_per_day;
    }
    m_totalMinutes = (m_totalMinutes % clock::minutes_per_day);
}

clock clock::at(minutes_t hour, minutes_t minute)
{
    const minutes_t total =
        ((hour * minutes_t{60}) + minute);

    return clock(total);
}

clock clock::add_minutes(minutes_t minutes) const
{
    return clock((m_totalMinutes + minutes));
}

clock clock::plus(minutes_t minutes) const
{
    return add_minutes(minutes);
}

std::string clock::to_string() const
{
    const minutes_t hour =
        (m_totalMinutes / minutes_t{60});
    const minutes_t minute =
        (m_totalMinutes % minutes_t{60});

    std::ostringstream oss;
    oss << std::setfill('0')
        << std::setw(2) << hour << ':'
        << std::setw(2) << minute;

    return oss.str();
}

clock::operator std::string() const
{
    return to_string();
}

bool operator==(const clock& lhs, const clock& rhs)
{
    return lhs.m_totalMinutes == rhs.m_totalMinutes;
}

bool operator!=(const clock& lhs, const clock& rhs)
{
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const clock& c)
{
    os << static_cast<std::string>(c);
    return os;
}

}  // namespace date_independent
