#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {

namespace {
// Return a positive modulo result for any integer `a`
int mod(int a, int b) {
    int r = a % b;
    return r < 0 ? r + b : r;
}
}  // unnamed namespace

// ---------------- Clock implementation ----------------

int Clock::normalize(int minutes) {
    return mod(minutes, 24 * 60); // 1440 minutes per day
}

Clock::Clock(int total_minutes) : total_minutes_{normalize(total_minutes)} {}

Clock Clock::at(int hour, int minute) {
    return Clock{hour * 60 + minute};
}

Clock Clock::plus(int minute) const {
    return Clock{total_minutes_ + minute};
}

Clock Clock::minus(int minute) const {
    return Clock{total_minutes_ - minute};
}

std::string Clock::to_string() const {
    int hours = total_minutes_ / 60;
    int minutes = total_minutes_ % 60;
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours << ":"
        << std::setw(2) << std::setfill('0') << minutes;
    return oss.str();
}

Clock::operator std::string() const {
    return to_string();
}

bool Clock::operator==(const Clock& other) const {
    return total_minutes_ == other.total_minutes_;
}

bool Clock::operator!=(const Clock& other) const {
    return !(*this == other);
}

}  // namespace date_independent
