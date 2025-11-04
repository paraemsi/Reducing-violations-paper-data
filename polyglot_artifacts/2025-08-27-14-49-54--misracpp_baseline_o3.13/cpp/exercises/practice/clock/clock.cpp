#include "clock.h"
#include <iomanip>
#include <sstream>
#include <ostream>

namespace date_independent {

namespace {
// Normalize any minute count to the range [0, 1439].
constexpr int MINUTES_IN_DAY = 24 * 60;
int normalize(int minutes) {
    minutes %= MINUTES_IN_DAY;
    if (minutes < 0) {
        minutes += MINUTES_IN_DAY;
    }
    return minutes;
}
}  // namespace

Clock::Clock(int hour, int minute)
    : total_minutes_{normalize(hour * 60 + minute)} {}

Clock Clock::plus(int minutes) const {
    return Clock{0, total_minutes_ + minutes};
}

Clock Clock::minus(int minutes) const {
    return Clock{0, total_minutes_ - minutes};
}

std::string Clock::str() const {
    int hour = total_minutes_ / 60;
    int minute = total_minutes_ % 60;
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hour << ':'
        << std::setfill('0') << std::setw(2) << minute;
    return oss.str();
}

bool Clock::operator==(const Clock& other) const {
    return total_minutes_ == other.total_minutes_;
}

bool Clock::operator!=(const Clock& other) const {
    return !(*this == other);
}

// Implicit conversion to std::string via member function.
Clock::operator std::string() const {
    return str();
}

namespace clock {
Clock at(int hour, int minute) {
    return Clock{hour, minute};
}
}  // namespace clock

// Stream insertion operator definition.
std::ostream& operator<<(std::ostream& os, const Clock& clock) {
    return os << clock.str();
}

}  // namespace date_independent
