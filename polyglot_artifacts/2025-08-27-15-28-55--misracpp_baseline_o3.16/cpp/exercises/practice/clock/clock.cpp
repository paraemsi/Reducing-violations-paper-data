#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

int Clock::normalize(int minutes)
{
    const int day_minutes = 24 * 60;
    minutes %= day_minutes;
    if (minutes < 0) {
        minutes += day_minutes;          // wrap backwards
    }
    return minutes;
}

// private ctor
Clock::Clock(int hour, int minute)
    : minutes_{normalize(hour * 60 + minute)}
{
}

// public factory
Clock Clock::at(int hour, int minute)
{
    return Clock{hour, minute};
}

Clock& Clock::plus(int minutes)
{
    minutes_ = normalize(minutes_ + minutes);
    return *this;
}

Clock& Clock::minus(int minutes)
{
    return plus(-minutes);
}

std::string Clock::to_string() const
{
    int hrs  = minutes_ / 60;
    int mins = minutes_ % 60;

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hrs << ':'
        << std::setfill('0') << std::setw(2) << mins;
    return oss.str();
}

bool Clock::operator==(const Clock& other) const
{
    return minutes_ == other.minutes_;
}

std::ostream& operator<<(std::ostream& os, const Clock& clk)
{
    return os << clk.to_string();
}

}  // namespace date_independent
