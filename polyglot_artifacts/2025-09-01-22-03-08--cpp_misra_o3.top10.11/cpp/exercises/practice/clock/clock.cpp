#include "clock.h"

#include <iomanip>
#include <sstream>
#include <ostream>

namespace date_independent {

std::int32_t clock::normalise(std::int32_t total_minutes) noexcept
{
    total_minutes = (total_minutes % minutes_per_day);
    if (total_minutes < static_cast<std::int32_t>(0))
    {
        total_minutes += minutes_per_day;
    }
    return total_minutes;
}

clock::clock(std::int32_t total_minutes) noexcept
    : _minutes(normalise(total_minutes))
{
}

clock clock::at(std::int32_t hour, std::int32_t minute) noexcept
{
    const std::int32_t total_minutes((hour * static_cast<std::int32_t>(60)) + minute);
    return clock(total_minutes);
}

clock& clock::plus(std::int32_t minute) noexcept
{
    _minutes = normalise((_minutes + minute));
    return *this;
}

clock& clock::minus(std::int32_t minute) noexcept
{
    _minutes = normalise((_minutes - minute));
    return *this;
}

std::string clock::to_string() const
{
    std::ostringstream oss;
    const std::int32_t hour((_minutes / static_cast<std::int32_t>(60)));
    const std::int32_t minute((_minutes % static_cast<std::int32_t>(60)));
    oss << std::setfill('0') << std::setw(2) << hour
        << ':' << std::setfill('0') << std::setw(2) << minute;
    return oss.str();
}

bool operator==(const clock& lhs, const clock& rhs) noexcept
{
    return lhs._minutes == rhs._minutes;
}

bool operator!=(const clock& lhs, const clock& rhs) noexcept
{
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const clock& clock_obj)
{
    os << clock_obj.to_string();
    return os;
}

}  // namespace date_independent
