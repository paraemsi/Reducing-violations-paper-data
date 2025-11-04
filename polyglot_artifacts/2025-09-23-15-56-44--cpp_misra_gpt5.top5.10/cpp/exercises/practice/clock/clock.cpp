#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

static constexpr std::int32_t kMinutesPerHour = static_cast<std::int32_t>(60);
static constexpr std::int32_t kHoursPerDay = static_cast<std::int32_t>(24);
static constexpr std::int32_t kMinutesPerDay = (kHoursPerDay * kMinutesPerHour);

std::int32_t clock::normalize(std::int32_t minutes)
{
    std::int32_t result = (minutes % kMinutesPerDay);
    if ((result < static_cast<std::int32_t>(0))) {
        result = (result + kMinutesPerDay);
    }
    return result;
}

clock::clock(std::int32_t hour, std::int32_t minute)
    : minutes_(clock::normalize(((hour * kMinutesPerHour) + minute)))
{
}

clock clock::at(std::int32_t hour, std::int32_t minute)
{
    return clock(hour, minute);
}

clock at(std::int32_t hour, std::int32_t minute)
{
    return clock(hour, minute);
}

clock clock::plus(std::int32_t minutes) const
{
    const std::int32_t delta = (minutes % kMinutesPerDay);
    const std::int32_t total = (minutes_ + delta);
    const std::int32_t norm = clock::normalize(total);
    return clock(static_cast<std::int32_t>(0), norm);
}

clock clock::minus(std::int32_t minutes) const
{
    const std::int32_t delta = (minutes % kMinutesPerDay);
    return plus(-delta);
}

std::string clock::str() const
{
    const std::int32_t hour = (minutes_ / kMinutesPerHour);
    const std::int32_t minute = (minutes_ % kMinutesPerHour);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hour << ':' << std::setw(2) << minute;
    return oss.str();
}

clock::operator std::string() const
{
    return str();
}

bool clock::operator==(const clock& other) const
{
    return (minutes_ == other.minutes_);
}

bool clock::operator!=(const clock& other) const
{
    return (minutes_ != other.minutes_);
}

}  // namespace date_independent
