#include "clock.h"

#include <sstream>
#include <iomanip>

constexpr std::int32_t date_independent::clock::minutes_in_day;

namespace date_independent {

clock clock::at(std::int32_t hour, std::int32_t minute) noexcept
{
    const std::int32_t total_minutes{((hour * 60) + minute)};
    return clock{total_minutes};
}

clock& clock::plus(std::int32_t minute) noexcept
{
    const std::int32_t updated{(minutes_since_midnight_ + minute)};
    minutes_since_midnight_ = ((updated % minutes_in_day) + minutes_in_day) % minutes_in_day;
    return *this;
}

clock& clock::minus(std::int32_t minute) noexcept
{
    return plus(static_cast<std::int32_t>(-minute));
}

std::string clock::to_string() const
{
    const std::int32_t hour{(minutes_since_midnight_ / 60)};
    const std::int32_t minute{(minutes_since_midnight_ % 60)};

    std::ostringstream oss{};
    oss << std::setw(2) << std::setfill('0') << hour << ':'
        << std::setw(2) << std::setfill('0') << minute;
    return oss.str();
}

bool clock::operator==(const clock& other) const noexcept
{
    return (minutes_since_midnight_ == other.minutes_since_midnight_);
}

clock::clock(std::int32_t total_minutes) noexcept
{
    minutes_since_midnight_ = ((total_minutes % minutes_in_day) + minutes_in_day) % minutes_in_day;
}

}  // namespace date_independent
