#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

auto clock::normalize_minutes(std::int32_t total_minutes) noexcept -> std::int32_t
{
    // Normalize into range [0, kMinutesPerDay)
    const std::int32_t mod = static_cast<std::int32_t>(total_minutes % kMinutesPerDay);
    const std::int32_t normalized = static_cast<std::int32_t>((mod + kMinutesPerDay) % kMinutesPerDay);
    return normalized;
}

auto clock::at(std::int32_t hour, std::int32_t minute) noexcept -> clock
{
    const std::int32_t total = static_cast<std::int32_t>((hour * kMinutesPerHour) + minute);
    const std::int32_t normalized = normalize_minutes(total);
    return clock(normalized);
}

auto clock::plus(std::int32_t minutes) const noexcept -> clock
{
    const std::int32_t total = static_cast<std::int32_t>(m_total_minutes + minutes);
    const std::int32_t normalized = normalize_minutes(total);
    return clock(normalized);
}

auto clock::minus(std::int32_t minutes) const noexcept -> clock
{
    const std::int32_t total = static_cast<std::int32_t>(m_total_minutes - minutes);
    const std::int32_t normalized = normalize_minutes(total);
    return clock(normalized);
}

auto clock::to_string() const -> std::string
{
    const std::int32_t hours = static_cast<std::int32_t>(m_total_minutes / kMinutesPerHour);
    const std::int32_t minutes = static_cast<std::int32_t>(m_total_minutes % kMinutesPerHour);

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours
        << ':'
        << std::setw(2) << std::setfill('0') << minutes;
    return oss.str();
}

clock::operator std::string() const
{
    return this->to_string();
}


auto to_string(const clock& c) -> std::string
{
    return c.to_string();
}

}  // namespace date_independent
