#include <cstdio>
#include "clock.h"

namespace date_independent {

// ---------- Clock private helpers ---------- //
int Clock::normalise(int total_minutes)
{
    // bring into [0, 1439]
    const int MINUTES_IN_DAY = 24 * 60;
    total_minutes %= MINUTES_IN_DAY;            // wrap (can be negative)
    if (total_minutes < 0)
        total_minutes += MINUTES_IN_DAY;
    return total_minutes;
}

Clock::Clock(int total_minutes)
    : minutes_{normalise(total_minutes)} {}

// ---------- Factory ---------- //
Clock Clock::at(int hour, int minute)
{
    int total = hour * 60 + minute;
    return Clock{total};
}

// ---------- Arithmetic ---------- //
Clock Clock::plus(int minutes) const
{
    return Clock{minutes_ + minutes};
}

Clock Clock::minus(int minutes) const
{
    return Clock{minutes_ - minutes};
}

// ---------- Representation ---------- //
std::string Clock::to_string() const
{
    int hour   = minutes_ / 60;
    int minute = minutes_ % 60;

    char buf[6];
    std::snprintf(buf, sizeof(buf), "%02d:%02d", hour, minute);
    return std::string{buf};
}

// ---------- Equality ---------- //
bool Clock::operator==(const Clock& other) const
{
    return minutes_ == other.minutes_;
}

}  // namespace date_independent
