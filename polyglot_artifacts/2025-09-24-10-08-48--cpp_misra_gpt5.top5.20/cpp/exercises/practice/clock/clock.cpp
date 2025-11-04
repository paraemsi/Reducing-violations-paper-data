#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {


clock::clock(std::int32_t hour, std::int32_t minute)
    : minutes_(
        normalize(
            (((hour % static_cast<std::int32_t>(24)) * static_cast<std::int32_t>(60))
             + (minute % minutes_per_day))
        )
    ) { }

std::int32_t clock::normalize(std::int32_t total) noexcept
{
    const std::int32_t m = minutes_per_day;
    std::int32_t res = (total % m);
    if (res < 0) {
        res = (res + m);
    }
    return res;
}

clock clock::plus(std::int32_t minutes) const
{
    const std::int32_t delta = (minutes % minutes_per_day);
    const std::int32_t total = (minutes_ + delta);
    const std::int32_t norm = normalize(total);
    return clock(static_cast<std::int32_t>(0), norm);
}

std::string clock::to_string() const
{
    const std::int32_t h = (minutes_ / static_cast<std::int32_t>(60));
    const std::int32_t m = (minutes_ % static_cast<std::int32_t>(60));
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << h << ':' << std::setw(2) << m;
    return oss.str();
}

clock::operator std::string() const
{
    return to_string();
}

bool operator==(const clock& lhs, const clock& rhs) noexcept
{
    return (lhs.minutes_ == rhs.minutes_);
}

bool operator!=(const clock& lhs, const clock& rhs) noexcept
{
    return (lhs.minutes_ != rhs.minutes_);
}

clock clock::at(std::int32_t hour, std::int32_t minute)
{
    return clock(hour, minute);
}

}  // namespace date_independent
