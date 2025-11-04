#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {

namespace
{
std::int32_t normalize(std::int32_t minutes) noexcept
{
    std::int32_t result = (minutes % Clock::MINUTES_PER_DAY);
    if (result < static_cast<std::int32_t>(0)) {
        result += Clock::MINUTES_PER_DAY;
    }
    return result;
}
} // unnamed namespace

Clock Clock::at(std::int32_t hour, std::int32_t minute) noexcept
{
    std::int32_t total = ((hour * static_cast<std::int32_t>(60)) + minute);
    return Clock(total);
}

Clock::Clock(std::int32_t hour, std::int32_t minute) noexcept
    : Clock((hour * static_cast<std::int32_t>(60)) + minute)
{
}

Clock::Clock(std::int32_t total_minutes) noexcept
    : m_minutes(normalize(total_minutes))
{
}

Clock Clock::plus(std::int32_t minute) const noexcept
{
    return Clock((m_minutes + minute));
}

Clock Clock::minus(std::int32_t minute) const noexcept
{
    return Clock((m_minutes - minute));
}

std::string Clock::to_string() const
{
    std::ostringstream oss;
    std::int32_t hours = (m_minutes / static_cast<std::int32_t>(60));
    std::int32_t mins  = (m_minutes % static_cast<std::int32_t>(60));

    oss << std::setw(2) << std::setfill('0') << hours << ':'
        << std::setw(2) << std::setfill('0') << mins;
    return oss.str();
}

Clock::operator std::string() const
{
    return to_string();
}

bool operator==(const Clock& lhs, const Clock& rhs) noexcept
{
    return (lhs.m_minutes == rhs.m_minutes);
}

bool operator!=(const Clock& lhs, const Clock& rhs) noexcept
{
    return !(lhs == rhs);
}

}  // namespace date_independent
