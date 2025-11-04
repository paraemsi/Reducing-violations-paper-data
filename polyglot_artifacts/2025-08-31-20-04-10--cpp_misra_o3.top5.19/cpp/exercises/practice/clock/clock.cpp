#include "clock.h"
#include <iomanip>
#include <sstream>
#include <ostream>

namespace date_independent {

std::int32_t clock::normalize(std::int32_t minutes)
{
    const std::int32_t day_minutes =
        static_cast<std::int32_t>(24) * static_cast<std::int32_t>(60);
    std::int32_t result = minutes % day_minutes;
    if(result < static_cast<std::int32_t>(0))
    {
        result += day_minutes;
    }
    return result;
}

clock clock::at(std::int32_t hour, std::int32_t minute)
{
    std::int32_t total = ((hour * static_cast<std::int32_t>(60)) + minute);
    return clock(total);
}

clock clock::plus(std::int32_t minutes) const
{
    return clock(minutes_ + minutes);
}

clock clock::minus(std::int32_t minutes) const
{
    return clock(minutes_ - minutes);
}

bool clock::operator==(const clock& other) const
{
    return (minutes_ == other.minutes_);
}

bool clock::operator!=(const clock& other) const
{
    return (minutes_ != other.minutes_);
}

std::string clock::to_string() const
{
    std::int32_t hour = minutes_ / static_cast<std::int32_t>(60);
    std::int32_t minute = minutes_ % static_cast<std::int32_t>(60);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hour
        << ':' << std::setfill('0') << std::setw(2)
        << minute;
    return oss.str();
}

clock::operator std::string() const
{
    return to_string();
}

// Private constructor
clock::clock(std::int32_t total_minutes) :
    minutes_(normalize(total_minutes))
{
}

std::ostream& operator<<(std::ostream& os, const clock& clk)
{
    os << clk.to_string();
    return os;
}

}  // namespace date_independent
