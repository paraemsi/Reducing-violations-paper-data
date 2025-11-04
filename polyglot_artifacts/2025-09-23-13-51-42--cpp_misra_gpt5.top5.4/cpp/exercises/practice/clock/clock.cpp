#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

namespace {
    constexpr std::int32_t minutes_per_hour{60};
    constexpr std::int32_t minutes_per_day{1440};
}

clock::clock(std::int32_t total_minutes_since_midnight) noexcept
    : minutes_since_midnight_(normalize(total_minutes_since_midnight)) {}

clock clock::at(std::int32_t hour, std::int32_t minute) noexcept {
    const std::int32_t total = ((hour * minutes_per_hour) + minute);
    return clock(total);
}

std::int32_t clock::normalize(std::int32_t total_minutes) noexcept {
    std::int32_t normalized = (total_minutes % minutes_per_day);
    if (normalized < 0) {
        normalized = (normalized + minutes_per_day);
    }
    return normalized;
}

clock clock::plus(std::int32_t minutes) const noexcept {
    const std::int32_t total = (minutes_since_midnight_ + minutes);
    return clock(total);
}

clock clock::minus(std::int32_t minutes) const noexcept {
    const std::int32_t total = (minutes_since_midnight_ - minutes);
    return clock(total);
}

std::string clock::to_string() const {
    const std::int32_t hours = (minutes_since_midnight_ / minutes_per_hour);
    const std::int32_t minutes = (minutes_since_midnight_ % minutes_per_hour);

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours
        << ':'
        << std::setw(2) << std::setfill('0') << minutes;
    return oss.str();
}

clock::operator std::string() const {
    return (to_string());
}

bool operator==(const clock& lhs, const clock& rhs) noexcept {
    return (lhs.minutes_since_midnight_ == rhs.minutes_since_midnight_);
}

bool operator!=(const clock& lhs, const clock& rhs) noexcept {
    return (!(lhs == rhs));
}

}  // namespace date_independent
