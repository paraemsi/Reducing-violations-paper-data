#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(std::int32_t minutes) : minutes_((minutes % 1440 + 1440) % 1440) {}

clock clock::at(std::int32_t hours, std::int32_t minutes) {
    // Convert to total minutes using int64_t to prevent overflow
    std::int64_t total_minutes = static_cast<std::int64_t>(hours) * 60 + minutes;
    // Normalize to be within 0-1439
    total_minutes %= 1440;
    if (total_minutes < 0) {
        total_minutes += 1440;
    }
    return clock(static_cast<std::int32_t>(total_minutes));
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
    // Ensure hours are within 0-23
    // Since minutes_ is always between 0-1439, hours will be between 0-23
    // Format to HH:MM
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
