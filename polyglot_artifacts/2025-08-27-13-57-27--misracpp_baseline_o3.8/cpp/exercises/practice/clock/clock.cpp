#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {

// ---------- Clock private helpers ----------

int Clock::mod(int value, int modulus) {
    return (value % modulus + modulus) % modulus;
}

Clock::Clock(int total_minutes) : minutes_{mod(total_minutes, minutes_in_day)} {}

// ---------- Factory ----------

Clock::Clock(int hour, int minute) : Clock(hour * 60 + minute) {}

Clock Clock::at(int hour, int minute) {
    return Clock{hour * 60 + minute};
}

// ---------- Arithmetic ----------

Clock Clock::plus(int delta_minutes) const {
    const int new_total = mod(minutes_ + delta_minutes, minutes_in_day);
    const int new_hour  = new_total / 60;
    const int new_min   = new_total % 60;
    return Clock{new_hour, new_min};
}

Clock Clock::minus(int delta_minutes) const {
    return plus(-delta_minutes);
}

// ---------- Representation ----------

std::string Clock::str() const {
    std::ostringstream os;
    os << std::setfill('0') << std::setw(2) << minutes_ / 60 << ':'
       << std::setfill('0') << std::setw(2) << minutes_ % 60;
    return os.str();
}

std::string Clock::to_string() const {
    return str();
}

Clock::operator std::string() const {
    return str();
}

// ---------- Comparison ----------

bool Clock::operator==(const Clock& other) const {
    return minutes_ == other.minutes_;
}

}  // namespace date_independent
