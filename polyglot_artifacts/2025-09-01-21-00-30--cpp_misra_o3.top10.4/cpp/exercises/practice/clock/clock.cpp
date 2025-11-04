#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

namespace
{
    /* Normalise a raw minute count so it falls inside one 24-hour day. */
    [[nodiscard]] std::int32_t normalize(std::int32_t total_minutes)
    {
        const std::int32_t modulo = Clock::minutes_per_day;
        /* Two-step modulo to guarantee a non-negative result. */
        const std::int32_t result =
            ((total_minutes % modulo) + modulo) % modulo;
        return result;
    }
} // unnamed namespace

Clock::Clock(std::int32_t total_minutes) :
    m_total_minutes(normalize(total_minutes))
{
}

Clock Clock::at(std::int32_t hour, std::int32_t minute)
{
    const std::int32_t total =
        ((hour * minutes_per_hour) + minute);
    return Clock(total);
}

std::string Clock::to_string() const
{
    std::ostringstream oss;
    const std::int32_t hour   = (m_total_minutes / minutes_per_hour);
    const std::int32_t minute = (m_total_minutes % minutes_per_hour);

    oss << std::setfill('0')
        << std::setw(2) << hour << ':'
        << std::setw(2) << minute;
    return oss.str();
}

Clock Clock::plus(std::int32_t minutes) const
{
    return Clock(m_total_minutes + minutes);
}

Clock Clock::minus(std::int32_t minutes) const
{
    return Clock(m_total_minutes - minutes);
}

bool operator==(const Clock& lhs, const Clock& rhs)
{
    return (lhs.m_total_minutes == rhs.m_total_minutes);
}

bool operator!=(const Clock& lhs, const Clock& rhs)
{
    return !(lhs == rhs);
}

/* Conversion operator implementation (out-of-line to avoid multiple definition
 * when the header is included in several translation units).
 */
std::string Clock::operator std::string() const
{
    return to_string();
}

}  // namespace date_independent
