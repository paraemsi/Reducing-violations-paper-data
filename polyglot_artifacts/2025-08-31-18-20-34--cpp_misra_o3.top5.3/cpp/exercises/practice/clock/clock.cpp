#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(minute_t total_minutes)
    : total_minutes_(normalize(total_minutes))
{
}

clock clock::at(minute_t hour, minute_t minute)
{
    minute_t total = (hour * static_cast<minute_t>(60)) + minute;
    return clock(total);
}

clock clock::plus(minute_t minutes) const
{
    return clock(total_minutes_ + minutes);
}

std::string clock::to_string() const
{
    minute_t hour = (total_minutes_ / static_cast<minute_t>(60));
    minute_t minute = (total_minutes_ % static_cast<minute_t>(60));

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hour << ':' << std::setfill('0') << std::setw(2) << minute;
    return oss.str();
}

clock::operator std::string() const
{
    return to_string();
}

bool clock::operator==(const clock& other) const
{
    return (total_minutes_ == other.total_minutes_);
}

bool clock::operator!=(const clock& other) const
{
    return (!(*this == other));
}

std::string string(const clock& c)
{
    return c.to_string();
}

clock::minute_t clock::normalize(minute_t minutes)
{
    constexpr minute_t kDayMinutes = static_cast<minute_t>(24 * 60);
    minute_t result = minutes % kDayMinutes;
    if(result < static_cast<minute_t>(0)) {
        result += kDayMinutes;
    }
    return result;
}

}  // namespace date_independent
