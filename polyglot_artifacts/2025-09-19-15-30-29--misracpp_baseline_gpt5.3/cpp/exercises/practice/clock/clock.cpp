#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(int total_minutes) : minutes_(normalize(total_minutes)) {}

int clock::normalize(int total_minutes) {
    int m = total_minutes % (24 * 60);
    if (m < 0) m += 24 * 60;
    return m;
}

clock clock::at(int hour, int minute) {
    int total = hour * 60 + minute;
    return clock(total);
}

clock clock::plus(int minutes) const {
    return clock(minutes_ + minutes);
}

clock clock::minus(int minutes) const {
    return clock(minutes_ - minutes);
}

clock::operator std::string() const {
    int hours = minutes_ / 60;
    int mins = minutes_ % 60;
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hours
        << ":" << std::setfill('0') << std::setw(2) << mins;
    return oss.str();
}

bool clock::operator==(const clock& other) const {
    return minutes_ == other.minutes_;
}

bool clock::operator!=(const clock& other) const {
    return !(*this == other);
}

std::string to_string(const clock& c) {
    return static_cast<std::string>(c);
}

}  // namespace date_independent
