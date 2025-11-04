#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

namespace
{
    /* Constants expressed with fixed-width types to avoid implicit conversions */
    constexpr std::int32_t kMinutesPerHour = static_cast<std::int32_t>(60);
    constexpr std::int32_t kMinutesPerDay  = static_cast<std::int32_t>(1440);
}

/* Private constructor – keeps minutes in range */
Clock::Clock(std::int32_t minutesSinceMidnight) : m_minutes(minutesSinceMidnight)
{
    if((m_minutes < static_cast<std::int32_t>(0)) ||
       (m_minutes >= kMinutesPerDay))
    {
        const std::int32_t wrapped =
            (((static_cast<std::int32_t>(m_minutes)
               % static_cast<std::int32_t>(kMinutesPerDay))
              + static_cast<std::int32_t>(kMinutesPerDay))
             % static_cast<std::int32_t>(kMinutesPerDay));
        m_minutes = wrapped;
    }
}

Clock Clock::at(std::int16_t hours, std::int16_t minutes)
{
    const std::int32_t total =
        (static_cast<std::int32_t>(hours) * static_cast<std::int32_t>(kMinutesPerHour))
        + static_cast<std::int32_t>(minutes);

    const std::int32_t wrapped =
        (((total % static_cast<std::int32_t>(kMinutesPerDay))
          + static_cast<std::int32_t>(kMinutesPerDay))
         % static_cast<std::int32_t>(kMinutesPerDay));

    return Clock(wrapped);
}

Clock Clock::addMinutes(std::int32_t minutes) const
{
    const std::int32_t total =
        static_cast<std::int32_t>(m_minutes) + minutes;

    const std::int32_t wrapped =
        (((total % static_cast<std::int32_t>(kMinutesPerDay))
          + static_cast<std::int32_t>(kMinutesPerDay))
         % static_cast<std::int32_t>(kMinutesPerDay));

    return Clock(wrapped);
}

Clock Clock::plus(std::int32_t minutes) const
{
    return addMinutes(minutes);
}

Clock Clock::minus(std::int32_t minutes) const
{
    return addMinutes(-minutes);
}

Clock::operator std::string() const
{
    return toString();
}

std::string Clock::toString() const
{
    std::ostringstream oss;

    const std::int32_t hours =
        static_cast<std::int32_t>(m_minutes) / static_cast<std::int32_t>(kMinutesPerHour);
    const std::int32_t minutes =
        static_cast<std::int32_t>(m_minutes) % static_cast<std::int32_t>(kMinutesPerHour);

    oss << std::setw(2) << std::setfill('0') << hours
        << ':'
        << std::setw(2) << std::setfill('0') << minutes;

    return oss.str();
}

/* Symmetrical comparison operators */
bool operator==(const Clock& lhs, const Clock& rhs)
{
    return (lhs.m_minutes == rhs.m_minutes);
}

bool operator!=(const Clock& lhs, const Clock& rhs)
{
    return !(lhs == rhs);
}

}  // namespace date_independent
