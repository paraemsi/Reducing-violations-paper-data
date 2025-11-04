#include "clock.h"

#include <iomanip>
#include <sstream>
#include <ostream>

namespace date_independent {

/* ---------- Clock private helpers --------------------------------------- */

Clock::Clock(std::int32_t minute_of_day) :
    m_minutes(normalise(minute_of_day))
{
    /* body intentionally left empty */
}

std::int32_t Clock::normalise(std::int32_t minute)
{
    /* bring minute into the positive domain first */
    std::int32_t result = ( (minute % MINUTES_PER_DAY) + MINUTES_PER_DAY ) % MINUTES_PER_DAY;
    return result;
}

/* ---------- Factory ------------------------------------------------------ */

Clock Clock::at(std::int32_t hour, std::int32_t minute)
{
    /* Convert hour + minute to total minutes,
       guarding against invalid hour/minute is left to tests */
    std::int32_t total = (hour * static_cast<std::int32_t>(60)) + minute;
    return Clock(total);
}

/* ---------- Modifying operations ---------------------------------------- */

Clock& Clock::plus(std::int32_t minute)
{
    m_minutes = normalise(m_minutes + minute);
    return *this;
}

Clock& Clock::minus(std::int32_t minute)
{
    m_minutes = normalise(m_minutes - minute);
    return *this;
}

/* ---------- Representation ---------------------------------------------- */

std::string Clock::to_string() const
{
    std::ostringstream oss;
    std::int32_t hours = m_minutes / static_cast<std::int32_t>(60);
    std::int32_t minutes = m_minutes % static_cast<std::int32_t>(60);

    oss << std::setw(2) << std::setfill('0') << hours
        << ':'
        << std::setw(2) << std::setfill('0') << minutes;

    return oss.str();
}

/* ---------- Comparison --------------------------------------------------- */

bool operator==(const Clock& lhs, const Clock& rhs)
{
    return (lhs.m_minutes == rhs.m_minutes);
}

bool operator!=(const Clock& lhs, const Clock& rhs)
{
    return !(lhs == rhs);
}

/* ---------- Conversions -------------------------------------------------- */

Clock::operator std::string() const
{
    return to_string();
}

/* ---------- Stream insertion -------------------------------------------- */

std::ostream& operator<<(std::ostream& os, const Clock& clk)
{
    os << clk.to_string();
    return os;
}

}  // namespace date_independent
