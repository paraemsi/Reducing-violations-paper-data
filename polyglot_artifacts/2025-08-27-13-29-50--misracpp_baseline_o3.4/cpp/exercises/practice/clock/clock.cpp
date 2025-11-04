#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {

// ---- Clock private helpers -------------------------------------------------
int Clock::normalize(int hour, int minute)
{
    // convert to total minutes then wrap into one day
    int total = hour * 60 + minute;
    return wrap(total);
}

int Clock::wrap(int total_minutes)
{
    // Proper mathematical modulo for negatives
    const int minutes_per_day = 24 * 60;
    int result = total_minutes % minutes_per_day;
    if (result < 0)
        result += minutes_per_day;
    return result;
}

// ---- Constructors / factory ------------------------------------------------
Clock::Clock(int total_minutes)
    : m_total_minutes(static_cast<int16_t>(wrap(total_minutes))) {}

Clock Clock::at(int hour, int minute)
{
    return Clock(normalize(hour, minute));
}

// ---- Public API ------------------------------------------------------------
Clock Clock::plus(int minutes) const
{
    return Clock(m_total_minutes + minutes);
}

Clock Clock::minus(int minutes) const
{
    return Clock(m_total_minutes - minutes);
}

std::string Clock::to_string() const
{
    std::ostringstream out;
    int hours = m_total_minutes / 60;
    int mins  = m_total_minutes % 60;
    out << std::setw(2) << std::setfill('0') << hours << ':'
        << std::setw(2) << std::setfill('0') << mins;
    return out.str();
}

// ---- Equality --------------------------------------------------------------
bool Clock::operator==(const Clock& other) const
{
    return m_total_minutes == other.m_total_minutes;
}

// ---- Stream operator -------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Clock& clock)
{
    return os << clock.to_string();
}

}  // namespace date_independent
