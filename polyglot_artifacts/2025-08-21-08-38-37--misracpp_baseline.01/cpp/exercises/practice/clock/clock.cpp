#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(int hour, int minute) {
    minutes_since_midnight_ = normalize(hour * 60 + minute);
}

clock clock::at(int hour, int minute) {
    return clock(hour, minute);
}

clock clock::plus(int minutes) const {
    return clock(0, normalize(minutes_since_midnight_ + minutes));
}

clock clock::minus(int minutes) const {
    return clock(0, normalize(minutes_since_midnight_ - minutes));
}

std::string clock::to_string() const {
    int hour = minutes_since_midnight_ / 60;
    int minute = minutes_since_midnight_ % 60;
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hour << ":"
        << std::setw(2) << std::setfill('0') << minute;
    return oss.str();
}

bool clock::operator==(const clock& lhs, const clock& rhs) {
    return lhs.minutes_since_midnight_ == rhs.minutes_since_midnight_;
}

int clock::normalize(int minutes) {
    int result = minutes % (24 * 60);
    if (result < 0)
        result += 24 * 60;
    return result;
}

}  // namespace date_independent
