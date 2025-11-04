#include "clock.h"

#include <cstdint>
#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(value_type normalized_minutes) noexcept
    : minutes_since_midnight_{normalized_minutes}
{
}

clock::value_type clock::normalize(value_type total_minutes) noexcept
{
    value_type result = (total_minutes % kMinutesPerDay);
    if ((result < static_cast<value_type>(0))) {
        result = (result + kMinutesPerDay);
    }
    return result;
}

clock clock::at(value_type hour, value_type minute) noexcept
{
    const value_type total = ((hour * kMinutesPerHour) + minute);
    return clock{normalize(total)};
}

clock clock::plus(value_type minutes) const noexcept
{
    const value_type total = (minutes_since_midnight_ + minutes);
    return clock{normalize(total)};
}

std::string clock::to_string() const
{
    const value_type hours = (minutes_since_midnight_ / kMinutesPerHour);
    const value_type mins = (minutes_since_midnight_ % kMinutesPerHour);

    std::ostringstream oss;
    (oss << std::setfill('0') << std::setw(2) << static_cast<std::int64_t>(hours));
    (oss << ":" << std::setw(2) << static_cast<std::int64_t>(mins));
    return oss.str();
}

bool operator==(const clock& lhs, const clock& rhs) noexcept
{
    return (lhs.minutes_since_midnight_ == rhs.minutes_since_midnight_);
}

bool operator!=(const clock& lhs, const clock& rhs) noexcept
{
    return (!(lhs == rhs));
}

}  // namespace date_independent
