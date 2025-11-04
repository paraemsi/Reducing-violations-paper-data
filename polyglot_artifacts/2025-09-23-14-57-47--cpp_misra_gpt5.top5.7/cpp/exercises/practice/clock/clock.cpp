#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

namespace {
static constexpr std::int32_t MINUTES_PER_DAY = static_cast<std::int32_t>(1440);
static constexpr std::int32_t MINUTES_PER_HOUR = static_cast<std::int32_t>(60);
}  // namespace

clock clock::at(std::int32_t hour, std::int32_t minute) noexcept
{
    const std::int32_t total = ((hour * MINUTES_PER_HOUR) + minute);
    return clock(clock::normalize_minutes(total));
}

clock::clock(std::int32_t normalized_minutes) noexcept
    : minutes_since_midnight_(clock::normalize_minutes(normalized_minutes))
{
}

std::int32_t clock::normalize_minutes(std::int32_t minutes_total) noexcept
{
    const std::int32_t mod = (minutes_total % MINUTES_PER_DAY);
    const std::int32_t normalized = ((mod + MINUTES_PER_DAY) % MINUTES_PER_DAY);
    return normalized;
}

clock clock::plus(std::int32_t minutes) const noexcept
{
    const std::int32_t total = (minutes_since_midnight_ + minutes);
    return clock(clock::normalize_minutes(total));
}

clock clock::minus(std::int32_t minutes) const noexcept
{
    const std::int32_t total = (minutes_since_midnight_ - minutes);
    return clock(clock::normalize_minutes(total));
}

std::string clock::to_string() const
{
    const std::int32_t hours = (minutes_since_midnight_ / MINUTES_PER_HOUR);
    const std::int32_t minutes = (minutes_since_midnight_ % MINUTES_PER_HOUR);

    std::ostringstream oss;
    oss << (std::setw(2)) << (std::setfill('0')) << hours
        << (":") << (std::setw(2)) << (std::setfill('0')) << minutes;
    return oss.str();
}

clock::operator std::string() const
{
    return to_string();
}

bool clock::operator==(const clock& other) const noexcept
{
    return (minutes_since_midnight_ == other.minutes_since_midnight_);
}

bool clock::operator!=(const clock& other) const noexcept
{
    return (!(operator==(other)));
}

}  // namespace date_independent
