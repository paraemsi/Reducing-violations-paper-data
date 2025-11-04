#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

int clock::normalise(int minutes)
{
    minutes %= 24 * 60;          // one day = 1 440 minutes
    if (minutes < 0)
        minutes += 24 * 60;
    return minutes;
}

clock::clock(int minutes_since_midnight)
    : minutes_{normalise(minutes_since_midnight)}
{}

clock clock::at(int hour, int minute)
{
    return clock{hour * 60 + minute};
}

std::string clock::to_string() const
{
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << minutes_ / 60
        << ':'
        << std::setw(2) << std::setfill('0') << minutes_ % 60;
    return oss.str();
}

clock clock::plus(int minutes) const
{
    return clock{ minutes_ + minutes };
}

clock clock::minus(int minutes) const
{
    return plus(-minutes);
}

bool operator==(const clock& lhs, const clock& rhs)
{
    return lhs.minutes_ == rhs.minutes_;
}

}  // namespace date_independent
