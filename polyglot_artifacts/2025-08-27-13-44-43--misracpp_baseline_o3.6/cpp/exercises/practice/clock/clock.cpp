#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

/* static */ clock clock::at(int hour, int minute)
{
    int total = hour * 60 + minute;
    return clock{ normalise(total) };
}

clock clock::plus(int minutes) const
{
    return clock{ normalise(minutes_ + minutes) };
}

clock clock::minus(int minutes) const
{
    return clock{ normalise(minutes_ - minutes) };
}

std::string clock::to_string() const
{
    int h = minutes_ / 60;
    int m = minutes_ % 60;
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << h << ':'
        << std::setfill('0') << std::setw(2) << m;
    return oss.str();
}

/* static */ int clock::normalise(int minutes)
{
    minutes %= 24 * 60;          // wrap around by one day
    if (minutes < 0) {
        minutes += 24 * 60;      // handle negative values
    }
    return minutes;
}

}  // namespace date_independent
