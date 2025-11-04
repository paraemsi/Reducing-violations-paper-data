#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {
using minutes_t = Clock::minutes_t;  /* bring nested alias into this namespace scope */

/* -----------  private helpers ------------- */
Clock::minutes_t Clock::normalize(minutes_t total_minutes)
{
    /* ensure result is within [0, 1 440) */
    minutes_t const minutes_per_day = static_cast<minutes_t>(24) * static_cast<minutes_t>(60);
    minutes_t const result = ((total_minutes % minutes_per_day) + minutes_per_day) % minutes_per_day;
    return result;
}

/* -----------  constructors / factories ------------- */
Clock::Clock(minutes_t total_minutes) : m_minutes(normalize(total_minutes))
{
}

Clock Clock::at(minutes_t hour, minutes_t minute)
{
    minutes_t const total = (hour * static_cast<minutes_t>(60)) + minute;
    return Clock(total);
}

/* -----------  public operations ------------- */
Clock Clock::plus(minutes_t minute_offset) const
{
    minutes_t const total = m_minutes + minute_offset;
    return Clock(total);
}

std::string Clock::to_string() const
{
    minutes_t const hour   = m_minutes / static_cast<minutes_t>(60);
    minutes_t const minute = m_minutes % static_cast<minutes_t>(60);

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hour
        << ':'                                         /* NOLINT */
        << std::setw(2) << std::setfill('0') << minute;
    return oss.str();
}

/* -----------  comparisons ------------- */
bool Clock::operator==(Clock const& other) const
{
    return m_minutes == other.m_minutes;
}

bool Clock::operator!=(Clock const& other) const
{
    return !(*this == other);
}

}  // namespace date_independent
