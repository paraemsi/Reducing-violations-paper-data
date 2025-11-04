#include "clock.h"
#include <iomanip>
#include <sstream>
#include <ostream>

namespace date_independent {

namespace {
/* Ensure modulo result is non-negative. */
constexpr minutes_t mod(minutes_t value,
                        minutes_t modulus) noexcept
{
    return (((value % modulus) + modulus) % modulus);
}
} // unnamed namespace

Clock Clock::at(minutes_t hour, minutes_t minute) noexcept
{
    /* Normalize inputs to minutes since midnight */
    minutes_t totalMinutes =
        ((hour * static_cast<minutes_t>(60)) + minute);

    return Clock{mod(totalMinutes, MINUTES_IN_DAY)};
}

Clock Clock::plus(minutes_t minutes) const noexcept
{
    return Clock{mod((m_minutesOfDay + minutes), MINUTES_IN_DAY)};
}

Clock Clock::minus(minutes_t minutes) const noexcept
{
    return Clock{mod((m_minutesOfDay - minutes), MINUTES_IN_DAY)};
}

bool Clock::operator==(const Clock& other) const noexcept
{
    return (m_minutesOfDay == other.m_minutesOfDay);
}

bool Clock::operator!=(const Clock& other) const noexcept
{
    return (m_minutesOfDay != other.m_minutesOfDay);
}

std::string Clock::to_string() const
{
    std::ostringstream oss;
    minutes_t hour   = (m_minutesOfDay / static_cast<minutes_t>(60));
    minutes_t minute = (m_minutesOfDay % static_cast<minutes_t>(60));

    oss << std::setw(2) << std::setfill('0') << hour << ':'
        << std::setw(2) << std::setfill('0') << minute;

    return oss.str();
}

Clock::operator std::string() const
{
    return to_string();
}

std::ostream& operator<<(std::ostream& os, const Clock& clock)
{
    /* Stream insertion uses the existing string representation. */
    os << clock.to_string();
    return os;
}

Clock::Clock(minutes_t normalizedMinutes) noexcept
    : m_minutesOfDay{mod(normalizedMinutes, MINUTES_IN_DAY)}
{
}

}  // namespace date_independent
