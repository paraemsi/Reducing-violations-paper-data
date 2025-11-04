#include "clock.h"

#include <cstdint>
#include <sstream>
#include <iomanip>

namespace date_independent {

namespace
{
constexpr std::int32_t minutes_per_hour{60};
constexpr std::int32_t minutes_per_day{(24 * minutes_per_hour)};

/*
 * Normalise an absolute minute count so that the result is
 * within the inclusive range [0, 1439].
 */
auto normalize_minutes(std::int32_t minutes) noexcept -> std::int32_t
{
    std::int32_t result{(minutes % minutes_per_day)};
    if (result < 0)
    {
        result += minutes_per_day;
    }
    return result;
}
} // unnamed namespace

Clock::Clock(std::int32_t total_minutes) noexcept
    : m_total_minutes{normalize_minutes(total_minutes)}
{
}

Clock Clock::at(std::int32_t hour, std::int32_t minute) noexcept
{
    std::int32_t total{((hour * minutes_per_hour) + minute)};
    return Clock{total};
}

Clock Clock::plus(std::int32_t minutes) const noexcept
{
    return Clock{(m_total_minutes + minutes)};
}

Clock Clock::minus(std::int32_t minutes) const noexcept
{
    return Clock{(m_total_minutes - minutes)};
}

bool Clock::operator==(const Clock& other) const noexcept
{
    return (m_total_minutes == other.m_total_minutes);
}

bool Clock::operator!=(const Clock& other) const noexcept
{
    return !(*this == other);
}

Clock::operator std::string() const noexcept
{
    return to_string();
}

std::string Clock::to_string() const
{
    std::int32_t hour{(m_total_minutes / minutes_per_hour)};
    std::int32_t minute{(m_total_minutes % minutes_per_hour)};

    std::ostringstream oss{};
    oss.fill('0');
    oss << std::setw(2) << hour << ':' << std::setw(2) << minute;

    return oss.str();
}

}  // namespace date_independent
