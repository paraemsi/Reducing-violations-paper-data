#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {

Clock Clock::at(std::int32_t hour, std::int32_t minute)
{
    constexpr std::int32_t minutes_per_hour { static_cast<std::int32_t>(60) };
    std::int32_t total_minutes {
        static_cast<std::int32_t>((hour * minutes_per_hour) + minute)
    };
    total_minutes = (
        ((total_minutes % Clock::kMinutesPerDay) + Clock::kMinutesPerDay)
        % Clock::kMinutesPerDay
    );
    return Clock { total_minutes };
}

Clock Clock::plus(std::int32_t minutes) const noexcept
{
    Clock result { minutes_ };
    result.adjust(minutes);
    return result;
}

Clock Clock::minus(std::int32_t minutes) const noexcept
{
    Clock result { minutes_ };
    result.adjust(static_cast<std::int32_t>(-minutes));
    return result;
}

std::string Clock::to_string() const
{
    std::int32_t hour_part {
        static_cast<std::int32_t>(minutes_ / static_cast<std::int32_t>(60))
    };
    std::int32_t minute_part {
        static_cast<std::int32_t>(minutes_ % static_cast<std::int32_t>(60))
    };

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hour_part << ':'
        << std::setfill('0') << std::setw(2) << minute_part;
    return oss.str();
}

Clock::operator std::string() const noexcept
{
    return to_string();
}

bool operator==(const Clock& lhs, const Clock& rhs) noexcept
{
    return (lhs.minutes_ == rhs.minutes_);
}

bool operator!=(const Clock& lhs, const Clock& rhs) noexcept
{
    return (lhs.minutes_ != rhs.minutes_);
}

Clock::Clock(std::int32_t total_minutes) noexcept : minutes_(total_minutes)
{
    /* Value assumed normalised by factory method */
}

void Clock::adjust(std::int32_t delta) noexcept
{
    minutes_ = (
        ((minutes_ + delta) % kMinutesPerDay) + kMinutesPerDay
    ) % kMinutesPerDay;
}

}  // namespace date_independent
