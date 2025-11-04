#include "clock.h"
#include <sstream>
#include <iomanip>

namespace {
constexpr std::int32_t MINUTES_PER_HOUR = static_cast<std::int32_t>(60);
constexpr std::int32_t HOURS_PER_DAY = static_cast<std::int32_t>(24);
constexpr std::int32_t MINUTES_PER_DAY = (MINUTES_PER_HOUR * HOURS_PER_DAY);

std::int32_t normalize(std::int64_t total_minutes) noexcept
{
    const std::int64_t m_per_day64 = static_cast<std::int64_t>(MINUTES_PER_DAY);
    const std::int64_t mod = (total_minutes % m_per_day64);
    const bool negative = (mod < static_cast<std::int64_t>(0));
    const std::int64_t normalized64 = negative ? (mod + m_per_day64) : mod;
    return static_cast<std::int32_t>(normalized64);
}
}  // unnamed namespace

namespace date_independent {

namespace clock {

Clock::Clock(std::int32_t hour, std::int32_t minute) noexcept
    : m_minutes(normalize(((static_cast<std::int64_t>(hour) * static_cast<std::int64_t>(MINUTES_PER_HOUR)) + static_cast<std::int64_t>(minute))))
{
}

Clock Clock::at(std::int32_t hour, std::int32_t minute) noexcept
{
    return Clock(hour, minute);
}

Clock at(std::int32_t hour, std::int32_t minute) noexcept
{
    return Clock(hour, minute);
}

Clock Clock::plus(std::int32_t minutes) const noexcept
{
    const std::int32_t nm = normalize((static_cast<std::int64_t>(m_minutes) + static_cast<std::int64_t>(minutes)));
    const std::int32_t hh = (nm / MINUTES_PER_HOUR);
    const std::int32_t mm = (nm % MINUTES_PER_HOUR);
    return Clock(hh, mm);
}

Clock Clock::minus(std::int32_t minutes) const noexcept
{
    return plus(static_cast<std::int32_t>(0) - minutes);
}

std::string Clock::to_string() const
{
    const std::int32_t hh = (m_minutes / MINUTES_PER_HOUR);
    const std::int32_t mm = (m_minutes % MINUTES_PER_HOUR);
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hh
        << ":" << std::setw(2) << std::setfill('0') << mm;
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
    return (lhs.m_minutes != rhs.m_minutes);
}

}  // namespace clock

}  // namespace date_independent
