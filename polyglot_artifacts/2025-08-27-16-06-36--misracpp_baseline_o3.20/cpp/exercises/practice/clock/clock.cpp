#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

namespace {
// Normalize a minute count to the range [0, 1440)
int normalize(int minutes) {
    const int day = 24 * 60;
    minutes %= day;
    if (minutes < 0) {
        minutes += day;
    }
    return minutes;
}
} // namespace

clock::clock(int hour, int minute) {
    total_minutes = normalize(hour * 60 + minute);
}

clock clock::plus(int mins) const {
    int new_total = normalize(total_minutes + mins);
    return clock(new_total / 60, new_total % 60);
}

clock clock::minus(int mins) const {
    return plus(-mins);
}

std::string clock::str() const {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << total_minutes / 60 << ':'
        << std::setfill('0') << std::setw(2) << total_minutes % 60;
    return oss.str();
}

std::string clock::to_string() const {
    return str();
}

clock::operator std::string() const {
    return str();
}

clock clock::at(int hour, int minute) {
    return clock(hour, minute);
}

bool operator==(const clock& lhs, const clock& rhs) {
    return lhs.total_minutes == rhs.total_minutes;
}

bool operator!=(const clock& lhs, const clock& rhs) {
    return !(lhs == rhs);
}

clock at(int hour, int minute) {
    return clock(hour, minute);
}

}  // namespace date_independent
