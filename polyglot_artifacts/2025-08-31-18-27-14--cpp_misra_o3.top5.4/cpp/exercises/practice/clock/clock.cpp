#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {

Clock Clock::at(std::int32_t hour, std::int32_t minute)
{
    const std::int32_t total_minutes_unwrapped =
        (hour * static_cast<std::int32_t>(60)) + minute;
    return Clock(total_minutes_unwrapped);
}

Clock Clock::plus(std::int32_t minutes) const
{
    const std::int32_t new_total = minutes_ + minutes;
    return Clock(new_total);
}

Clock Clock::minus(std::int32_t minutes) const
{
    return plus(static_cast<std::int32_t>(-minutes));
}

std::string Clock::to_string() const
{
    std::ostringstream oss;
    const std::int32_t hour   = minutes_ / static_cast<std::int32_t>(60);
    const std::int32_t minute = minutes_ % static_cast<std::int32_t>(60);
    oss << std::setfill('0') << std::setw(2) << hour << ':'
        << std::setfill('0') << std::setw(2) << minute;
    return oss.str();
}

Clock::operator std::string() const
{
    return to_string();
}

bool Clock::operator==(const Clock& other) const
{
    return (minutes_ == other.minutes_);
}

bool Clock::operator!=(const Clock& other) const
{
    return (minutes_ != other.minutes_);
}

Clock::Clock(std::int32_t total_minutes)
{
    std::int32_t adjusted = total_minutes % kMinutesPerDay;
    if(adjusted < static_cast<std::int32_t>(0)) {
        adjusted += kMinutesPerDay;
    }
    minutes_ = adjusted;
}

}  // namespace date_independent
