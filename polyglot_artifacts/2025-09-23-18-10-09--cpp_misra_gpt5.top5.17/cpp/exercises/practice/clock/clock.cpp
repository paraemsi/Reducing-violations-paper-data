#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {

namespace {
constexpr std::int32_t kMinutesPerHour = static_cast<std::int32_t>(60);
constexpr std::int32_t kHoursPerDay = static_cast<std::int32_t>(24);
constexpr std::int32_t kMinutesPerDay = static_cast<std::int32_t>(kHoursPerDay * kMinutesPerHour);
}  // namespace

std::int32_t clock::normalize_total_minutes(std::int32_t total_minutes) noexcept
{
    std::int32_t r = (total_minutes % kMinutesPerDay);
    if ((r < static_cast<std::int32_t>(0))) {
        r = (r + kMinutesPerDay);
    } else {
        // no adjustment needed
    }
    return r;
}

clock::clock(std::int32_t total_minutes) noexcept
    : minutes_from_midnight_(normalize_total_minutes(total_minutes))
{
}

clock clock::at(std::int32_t hour, std::int32_t minute) noexcept
{
    const std::int32_t total = ((hour * kMinutesPerHour) + minute);
    return clock(total);
}

clock clock::plus(std::int32_t minutes) const noexcept
{
    const std::int32_t sum = (minutes_from_midnight_ + minutes);
    return clock(sum);
}

clock clock::minus(std::int32_t minutes) const noexcept
{
    const std::int32_t diff = (minutes_from_midnight_ - minutes);
    return clock(diff);
}

std::string clock::to_string() const
{
    const std::int32_t hour = (minutes_from_midnight_ / kMinutesPerHour);
    const std::int32_t minute = (minutes_from_midnight_ % kMinutesPerHour);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(static_cast<std::streamsize>(2)) << hour
        << ':'
        << std::setfill('0') << std::setw(static_cast<std::streamsize>(2)) << minute;
    return oss.str();
}

clock::operator std::string() const
{
    return to_string();
}

bool operator==(const clock& lhs, const clock& rhs) noexcept
{
    return (lhs.minutes_from_midnight_ == rhs.minutes_from_midnight_);
}

bool operator!=(const clock& lhs, const clock& rhs) noexcept
{
    return (lhs.minutes_from_midnight_ != rhs.minutes_from_midnight_);
}

}  // namespace date_independent
