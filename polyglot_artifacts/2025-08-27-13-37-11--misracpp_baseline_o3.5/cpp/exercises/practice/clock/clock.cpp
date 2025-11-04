#include "clock.h"
#include <iomanip>
#include <sstream>
#include <ostream>

namespace date_independent {

namespace {
constexpr int kMinutesPerDay = 24 * 60;

int normalize_minutes(int minutes) {
    int result = minutes % kMinutesPerDay;
    if (result < 0) result += kMinutesPerDay;
    return result;
}
} // unnamed namespace

// private constructor
clock::clock(int total_minutes)
    : minutes_(normalize_minutes(total_minutes)) {}

// static factory
clock clock::at(int hour, int minute) {
    return clock(hour * 60 + minute);
}

// static normalization helper
int clock::normalize(int total_minutes) {
    return normalize_minutes(total_minutes);
}

clock clock::plus(int minutes) const {
    return clock(minutes_ + minutes);
}

clock clock::minus(int minutes) const {
    return clock(minutes_ - minutes);
}

bool clock::operator==(const clock& other) const {
    return minutes_ == other.minutes_;
}

std::string clock::to_string() const {
    int h = minutes_ / 60;
    int m = minutes_ % 60;
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << h << ':'
        << std::setw(2) << std::setfill('0') << m;
    return oss.str();
}

clock::operator std::string() const {
    return to_string();
}

// stream insertion operator
std::ostream& operator<<(std::ostream& os, const clock& c) {
    return os << c.to_string();
}

}  // namespace date_independent
