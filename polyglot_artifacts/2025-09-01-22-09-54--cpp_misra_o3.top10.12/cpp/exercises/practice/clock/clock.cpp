#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(std::int32_t total_minutes)
    : minutes_since_midnight_{ normalise(total_minutes) }
{
}

clock clock::at(std::int32_t hour, std::int32_t minute)
{
    /* Convert hour / minute into absolute minutes, then construct */
    const std::int32_t total{
        ((hour * static_cast<std::int32_t>(60)) + minute)
    };
    return clock{ total };
}

clock clock::plus(std::int32_t minute_delta) const
{
    return clock{ clock::normalise((minutes_since_midnight_ + minute_delta)) };
}

clock clock::minus(std::int32_t minute_delta) const
{
    return clock{ clock::normalise((minutes_since_midnight_ - minute_delta)) };
}

std::string clock::to_string() const
{
    std::ostringstream oss{};
    oss << std::setfill('0')
        << std::setw(2)
        << (minutes_since_midnight_ / static_cast<std::int32_t>(60))
        << ':'
        << std::setfill('0')
        << std::setw(2)
        << (minutes_since_midnight_ % static_cast<std::int32_t>(60));
    return oss.str();
}

std::int32_t clock::normalise(std::int32_t total_minutes)
{
    /* Ensure the result is always within [0, minutes_per_day) */
    const std::int32_t wrapped{
        ((total_minutes % clock::minutes_per_day) + clock::minutes_per_day) % clock::minutes_per_day
    };
    return wrapped;
}

bool operator==(const clock& lhs, const clock& rhs)
{
    return (lhs.minutes_since_midnight_ == rhs.minutes_since_midnight_);
}

bool operator!=(const clock& lhs, const clock& rhs)
{
    return !(lhs == rhs);
}

}  // namespace date_independent
