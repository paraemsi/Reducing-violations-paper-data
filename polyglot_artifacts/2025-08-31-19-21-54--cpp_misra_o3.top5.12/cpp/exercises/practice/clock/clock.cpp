#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(minute_type hours, minute_type minutes)
    : total_minutes_(normalise((hours * static_cast<minute_type>(60)) + minutes))
{
}

clock clock::at(minute_type hours, minute_type minutes)
{
    return clock(hours, minutes);
}

clock clock::plus(minute_type minutes) const
{
    return clock(static_cast<minute_type>(0), (total_minutes_ + minutes));
}

clock clock::minus(minute_type minutes) const
{
    return clock(static_cast<minute_type>(0), (total_minutes_ - minutes));
}

std::string clock::to_string() const
{
    minute_type const hours = total_minutes_ / static_cast<minute_type>(60);
    minute_type const minutes = total_minutes_ % static_cast<minute_type>(60);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hours << ':'
        << std::setfill('0') << std::setw(2) << minutes;
    return oss.str();
}

clock::operator std::string() const
{
    return to_string();
}

bool operator==(const clock& lhs, const clock& rhs)
{
    return (lhs.total_minutes_ == rhs.total_minutes_);
}

bool operator!=(const clock& lhs, const clock& rhs)
{
    return !(lhs == rhs);
}

clock::minute_type clock::normalise(minute_type minutes)
{
    minute_type const modulo = static_cast<minute_type>(1440);
    minute_type result = minutes % modulo;
    if (result < static_cast<minute_type>(0)) {
        result += modulo;
    }
    return result;
}

}  // namespace date_independent
