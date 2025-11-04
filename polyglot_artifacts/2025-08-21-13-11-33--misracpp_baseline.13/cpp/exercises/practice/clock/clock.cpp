#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(int hour, int minute)
    : hour_(hour), minute_(minute) {
    normalize();
}

clock clock::at(int hour, int minute) {
    return clock(hour, minute);
}

clock clock::plus(int minutes) const {
    clock result(hour_, minute_ + minutes);
    return result;
}

clock clock::minus(int minutes) const {
    clock result(hour_, minute_ - minutes);
    return result;
}

std::string clock::to_string() const {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hour_ << ":"
        << std::setw(2) << std::setfill('0') << minute_;
    return oss.str();
}

bool clock::operator==(const clock& other) const {
    return hour_ == other.hour_ && minute_ == other.minute_;
}

bool clock::operator!=(const clock& other) const {
    return !(*this == other);
}

void clock::normalize() {
    int total_minutes = hour_ * 60 + minute_;
    total_minutes = ((total_minutes % 1440) + 1440) % 1440; // 1440 = 24*60
    hour_ = total_minutes / 60;
    minute_ = total_minutes % 60;
}

}  // namespace date_independent
