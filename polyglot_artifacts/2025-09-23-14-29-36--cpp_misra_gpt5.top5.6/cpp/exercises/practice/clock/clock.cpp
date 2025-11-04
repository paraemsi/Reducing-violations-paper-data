#include "clock.h"

#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>

namespace date_independent {

static constexpr std::int32_t hours_per_day = static_cast<std::int32_t>(24);
static constexpr std::int32_t minutes_per_hour = static_cast<std::int32_t>(60);
static constexpr std::int32_t minutes_per_day = (hours_per_day * minutes_per_hour);

std::int32_t clock::normalize(std::int32_t minutes) noexcept
{
    std::int32_t result = (minutes % minutes_per_day);
    if ((result < static_cast<std::int32_t>(0))) {
        result = (result + minutes_per_day);
    }
    return result;
}

clock::clock(std::int32_t total_minutes) noexcept
    : minutes_(normalize(total_minutes))
{
}

clock clock::at(std::int32_t hour, std::int32_t minute) noexcept
{
    const std::int32_t total = ((hour * minutes_per_hour) + minute);
    return clock(total);
}

clock clock::plus(std::int32_t minutes) const noexcept
{
    return clock(normalize((minutes_ + minutes)));
}

clock clock::minus(std::int32_t minutes) const noexcept
{
    return clock(normalize((minutes_ - minutes)));
}

std::string clock::str() const
{
    const std::int32_t hour = (minutes_ / minutes_per_hour);
    const std::int32_t minute = (minutes_ % minutes_per_hour);

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hour
        << ":" << std::setw(2) << std::setfill('0') << minute;
    return oss.str();
}

clock::operator std::string() const
{
    return (str());
}

bool operator==(const clock& lhs, const clock& rhs) noexcept
{
    return (lhs.minutes_ == rhs.minutes_);
}

bool operator!=(const clock& lhs, const clock& rhs) noexcept
{
    return !(lhs == rhs);
}

}  // namespace date_independent
