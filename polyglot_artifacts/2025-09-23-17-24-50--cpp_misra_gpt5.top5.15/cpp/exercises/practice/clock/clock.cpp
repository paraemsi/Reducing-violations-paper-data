#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(std::int32_t normalized_minutes)
    : minutes_from_midnight_{normalized_minutes}
{
}

clock clock::at(std::int32_t hour, std::int32_t minute)
{
    const std::int32_t total = ((hour * kMinutesPerHour) + minute);
    const std::int32_t norm = normalize(total);
    return clock{norm};
}

clock clock::plus(std::int32_t minutes) const
{
    const std::int32_t delta = (minutes % kMinutesPerDay);
    const std::int32_t total = (minutes_from_midnight_ + delta);
    const std::int32_t norm = normalize(total);
    return clock{norm};
}

std::string clock::str() const
{
    const std::int32_t hours = (minutes_from_midnight_ / kMinutesPerHour);
    const std::int32_t minutes = (minutes_from_midnight_ % kMinutesPerHour);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << static_cast<std::int64_t>(hours)
        << ":" << std::setw(2) << static_cast<std::int64_t>(minutes);
    return oss.str();
}

bool operator==(const clock& lhs, const clock& rhs)
{
    return (lhs.minutes_from_midnight_ == rhs.minutes_from_midnight_);
}

bool operator!=(const clock& lhs, const clock& rhs)
{
    return (lhs.minutes_from_midnight_ != rhs.minutes_from_midnight_);
}

std::int32_t clock::normalize(std::int32_t total_minutes)
{
    std::int32_t result = (total_minutes % kMinutesPerDay);
    if (result < static_cast<std::int32_t>(0)) {
        result = (result + kMinutesPerDay);
    } else {
        // no operation
    }
    return result;
}

}  // namespace date_independent
