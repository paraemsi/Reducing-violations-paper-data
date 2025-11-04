#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(std::int32_t minutes) : minutes_((minutes % 1440 + 1440) % 1440) {}

clock clock::at(std::int32_t hours, std::int32_t minutes) {
    std::int32_t total_minutes = (hours * 60) + minutes;
    return clock((total_minutes % 1440 + 1440) % 1440);
}

clock clock::plus(std::int32_t minutes) const {
    return clock(minutes_ + minutes);
}

clock clock::minus(std::int32_t minutes) const {
    return clock(minutes_ - minutes);
}

clock::operator std::string() const {
    std::int32_t hours = minutes_ / 60;
    std::int32_t minutes = minutes_ % 60;
    
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours << ":"
        << std::setw(2) << std::setfill('0') << minutes;
    return oss.str();
}

bool clock::operator==(const clock& other) const {
    return (minutes_ == other.minutes_);
}

bool clock::operator!=(const clock& other) const {
    return (minutes_ != other.minutes_);
}

}  // namespace date_independent
