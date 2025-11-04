#include "clock.h"

#include <iomanip>
#include <sstream>
#include <ostream>

namespace date_independent {

constexpr int kMinutesPerDay = 24 * 60;

// Normalise value to [0, kMinutesPerDay)
static int normalize(int minutes) {
    minutes %= kMinutesPerDay;
    if (minutes < 0) {
        minutes += kMinutesPerDay;
    }
    return minutes;
}

/* -------- Clock implementation -------- */
Clock::Clock(int total_minutes)
    : minutes_(normalize(total_minutes)) {}

/* Factory */
Clock Clock::at(int hour, int minute) {
    return Clock(hour * 60 + minute);
}

/* Arithmetic */
Clock Clock::plus(int minutes) const {
    return Clock(minutes_ + minutes);
}

Clock Clock::minus(int minutes) const {
    return Clock(minutes_ - minutes);
}

/* String representation */
std::string Clock::to_string() const {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << minutes_ / 60 << ':'
        << std::setw(2) << std::setfill('0') << minutes_ % 60;
    return oss.str();
}

/* Implicit conversion */
Clock::operator std::string() const {
    return to_string();
}

/* Equality */
bool Clock::operator==(const Clock& other) const {
    return minutes_ == other.minutes_;
}

bool Clock::operator!=(const Clock& other) const {
    return !(*this == other);
}

/* Stream insertion */
std::ostream& operator<<(std::ostream& os, const Clock& clock) {
    return os << clock.to_string();
}

}  // namespace date_independent
