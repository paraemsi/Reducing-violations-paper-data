#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {

namespace {
constexpr int minutes_per_day = 24 * 60;

int normalize_minutes(int minutes) {
    int mod = minutes % minutes_per_day;
    if (mod < 0) mod += minutes_per_day;
    return mod;
}
} // namespace

clock::clock(int hour, int minute)
    : total_minutes_(normalize_minutes(hour * 60 + minute)) {}

clock clock::at(int hour, int minute) {
    return clock(hour, minute);
}

clock clock::plus(int minutes) const {
    return clock(0, total_minutes_ + minutes);
}

clock clock::minus(int minutes) const {
    return clock(0, total_minutes_ - minutes);
}

clock::operator std::string() const {
    int hours = total_minutes_ / 60;
    int minutes = total_minutes_ % 60;
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours
        << ':' << std::setw(2) << std::setfill('0') << minutes;
    return oss.str();
}

bool clock::operator==(const clock& rhs) const {
    return total_minutes_ == rhs.total_minutes_;
}

bool clock::operator!=(const clock& rhs) const {
    return !(*this == rhs);
}

std::string to_string(const clock& c) {
    return static_cast<std::string>(c);
}

std::ostream& operator<<(std::ostream& os, const clock& c) {
    return os << static_cast<std::string>(c);
}

}  // namespace date_independent
