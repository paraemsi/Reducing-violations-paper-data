#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

/* *****  Private helpers ************************************************** */

auto Clock::normalize(std::int32_t total_minutes) -> std::int32_t
{
    /* Ensure the value is within one day – always non-negative. */
    std::int32_t const minutes_per_day{ static_cast<std::int32_t>(1440) };
    std::int32_t const result{
        ( ( total_minutes % minutes_per_day ) + minutes_per_day ) % minutes_per_day
    };
    return result;
}

/* *****  Constructors / factories ***************************************** */

Clock::Clock(std::int32_t total_minutes)
    : m_total_minutes{ normalize(total_minutes) }
{
    /* empty */
}

auto Clock::at(std::int32_t hour, std::int32_t minute) -> Clock
{
    std::int32_t const minutes_per_hour{ static_cast<std::int32_t>(60) };
    std::int32_t const total_minutes{ (hour * minutes_per_hour) + minute };
    return Clock{ total_minutes };
}

/* *****  Public interface ************************************************* */

auto Clock::to_string() const -> std::string
{
    std::ostringstream out{};
    out << std::setfill('0')
        << std::setw(2) << (m_total_minutes / static_cast<std::int32_t>(60))
        << ':'
        << std::setw(2) << (m_total_minutes % static_cast<std::int32_t>(60));
    return out.str();
}

auto Clock::plus(std::int32_t minutes) const -> Clock
{
    return Clock{ m_total_minutes + minutes };
}

auto Clock::minus(std::int32_t minutes) const -> Clock
{
    return Clock{ m_total_minutes - minutes };
}

auto Clock::operator==(Clock const& other) const -> bool
{
    return (m_total_minutes == other.m_total_minutes);
}

auto Clock::operator!=(Clock const& other) const -> bool
{
    return (m_total_minutes != other.m_total_minutes);
}

Clock::operator std::string() const
{
    return to_string();
}

/* *****  Non-member operators ********************************************* */

auto operator+(Clock const& clk, std::int32_t minutes) -> Clock
{
    return clk.plus(minutes);
}

auto operator-(Clock const& clk, std::int32_t minutes) -> Clock
{
    return clk.minus(minutes);
}

}  // namespace date_independent
