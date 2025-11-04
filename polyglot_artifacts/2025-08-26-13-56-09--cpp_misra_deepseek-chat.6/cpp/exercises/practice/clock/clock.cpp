#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>
#include <cstdint>

namespace date_independent {

clock::clock(std::int32_t minutes) : minutes_(((minutes % (24 * 60)) + (24 * 60)) % (24 * 60)) {
}

clock clock::at(std::int32_t hours, std::int32_t minutes) {
    std::int32_t total_minutes = ((hours * 60) + minutes);
    return clock(total_minutes);
}

clock clock::plus(std::int32_t minutes_to_add) const {
    return clock((minutes_ + minutes_to_add));
}

clock clock::minus(std::int32_t minutes_to_subtract) const {
    return clock((minutes_ - minutes_to_subtract));
}

clock::operator std::string() const {
    std::int32_t hours = (minutes_ / 60);
    std::int32_t minutes = (minutes_ % 60);
    
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours << ":"
        << std::setw(2) << std::setfill('0') << minutes;
    return oss.str();
}

bool clock::operator==(const clock& other) const {
    return minutes_ == other.minutes_;
}

bool clock::operator!=(const clock& other) const {
    return minutes_ != other.minutes_;
}

}  // namespace date_independent
