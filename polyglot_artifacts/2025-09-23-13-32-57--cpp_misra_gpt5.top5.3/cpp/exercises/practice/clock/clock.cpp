#include "clock.h"

#include <cstdint>
#include <iomanip>
#include <sstream>

namespace date_independent {

namespace {
    constexpr std::int32_t minutes_per_hour = static_cast<std::int32_t>(60);
    constexpr std::int32_t hours_per_day = static_cast<std::int32_t>(24);
    constexpr std::int32_t minutes_per_day = static_cast<std::int32_t>(hours_per_day * minutes_per_hour);

    std::int32_t normalize_minutes(std::int32_t total) noexcept {
        const std::int32_t mod = static_cast<std::int32_t>(total % minutes_per_day);
        const std::int32_t adjusted = static_cast<std::int32_t>((mod + minutes_per_day) % minutes_per_day);
        return adjusted;
    }
}  // unnamed namespace

clock::clock(std::int32_t hour, std::int32_t minute) noexcept
    : minutes_since_midnight_(normalize_minutes(static_cast<std::int32_t>((hour * minutes_per_hour) + minute))) {
}

clock clock::at(std::int32_t hour, std::int32_t minute) noexcept {
    return clock(hour, minute);
}

clock clock::plus(std::int32_t minutes) const noexcept {
    const std::int32_t new_total = normalize_minutes(static_cast<std::int32_t>(minutes_since_midnight_ + minutes));
    const std::int32_t h = static_cast<std::int32_t>(new_total / minutes_per_hour);
    const std::int32_t m = static_cast<std::int32_t>(new_total % minutes_per_hour);
    return clock(h, m);
}

clock clock::minus(std::int32_t minutes) const noexcept {
    return plus(static_cast<std::int32_t>(-minutes));
}

std::string clock::str() const {
    const std::int32_t h = static_cast<std::int32_t>(minutes_since_midnight_ / minutes_per_hour);
    const std::int32_t m = static_cast<std::int32_t>(minutes_since_midnight_ % minutes_per_hour);

    std::ostringstream oss;
    oss.fill('0');
    oss << std::setw(2) << (h) << ':' << std::setw(2) << (m);
    return oss.str();
}

clock::operator std::string() const {
    return str();
}

bool operator==(const clock& lhs, const clock& rhs) noexcept {
    return (lhs.minutes_since_midnight_ == rhs.minutes_since_midnight_);
}

bool operator!=(const clock& lhs, const clock& rhs) noexcept {
    return (!(lhs == rhs));
}

clock at(std::int32_t hour, std::int32_t minute) noexcept {
    return clock(hour, minute);
}

}  // namespace date_independent
