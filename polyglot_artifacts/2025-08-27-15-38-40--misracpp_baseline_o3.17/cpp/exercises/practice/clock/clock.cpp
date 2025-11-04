#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

namespace {
    // Helper keeps minutes within a single day
    int normalize_minutes(int minutes) {
        const int kDayMinutes = 24 * 60;
        minutes %= kDayMinutes;
        if (minutes < 0) {
            minutes += kDayMinutes;
        }
        return minutes;
    }
}  // namespace

// ---- Clock private helpers -------------------------------------------------
int Clock::normalize(int minutes) {
    return normalize_minutes(minutes);
}

Clock::Clock(int minutes) : total_minutes_(normalize(minutes)) {}

// ---- Clock construction ----------------------------------------------------
Clock Clock::at(int hour, int minute) {
    return Clock(hour * 60 + minute);
}

// ---- Clock arithmetic ------------------------------------------------------
Clock Clock::plus(int minutes) const {
    return Clock(total_minutes_ + minutes);
}

Clock Clock::minus(int minutes) const {
    return Clock(total_minutes_ - minutes);
}

// ---- Output ----------------------------------------------------------------
std::string Clock::to_string() const {
    std::ostringstream oss;
    int hours = total_minutes_ / 60;
    int minutes = total_minutes_ % 60;
    oss << std::setw(2) << std::setfill('0') << hours << ':'
        << std::setw(2) << std::setfill('0') << minutes;
    return oss.str();
}

// ---- Equality --------------------------------------------------------------
bool operator==(const Clock& lhs, const Clock& rhs) {
    return lhs.total_minutes_ == rhs.total_minutes_;
}

}  // namespace date_independent
