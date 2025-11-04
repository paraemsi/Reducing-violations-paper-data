#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {

namespace {
constexpr int kMinutesPerDay{24 * 60};
}

// --- helper ---------------------------------------------------------------
int clock::normalize(int minutes) {
    minutes %= kMinutesPerDay;
    if (minutes < 0) {
        minutes += kMinutesPerDay;
    }
    return minutes;
}

// --- ctor -----------------------------------------------------------------
clock::clock(int hour, int minute)
    : minutes_{normalize(hour * 60 + minute)} {}

// --- factory --------------------------------------------------------------
clock clock::at(int hour, int minute) {
    return clock{hour, minute};
}

// --- arithmetic -----------------------------------------------------------
clock clock::plus(int minutes) const {
    return clock{0, minutes_ + minutes};
}

clock clock::minus(int minutes) const {
    return plus(-minutes);
}

 // --- formatting -----------------------------------------------------------
std::string clock::to_string() const {
    int hrs{minutes_ / 60};
    int mins{minutes_ % 60};

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hrs << ':'
        << std::setfill('0') << std::setw(2) << mins;

    return oss.str();
}

// --- conversion -----------------------------------------------------------
clock::operator std::string() const {
    return to_string();
}

// --- comparison -----------------------------------------------------------
bool clock::operator==(const clock& other) const {
    return minutes_ == other.minutes_;
}

bool clock::operator!=(const clock& other) const {
    return !(*this == other);
}

}  // namespace date_independent
