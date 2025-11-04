#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

namespace {
    constexpr std::int32_t hours_per_day = static_cast<std::int32_t>(24);
    constexpr std::int32_t minutes_per_hour = static_cast<std::int32_t>(60);
    constexpr std::int32_t minutes_per_day = (hours_per_day * minutes_per_hour);
}

clock::clock(std::int32_t total_minutes) noexcept
    : minutes_(clock::normalize(total_minutes)) {
}

clock clock::at(std::int32_t hour, std::int32_t minute) noexcept {
    const std::int32_t total = ((hour * minutes_per_hour) + minute);
    return clock(total);
}

std::int32_t clock::normalize(std::int32_t total_minutes) noexcept {
    std::int32_t m = (total_minutes % minutes_per_day);
    if (m < static_cast<std::int32_t>(0)) {
        m = (m + minutes_per_day);
    }
    return m;
}

clock clock::plus(std::int32_t minutes) const noexcept {
    const std::int32_t total = (minutes_ + minutes);
    return clock(total);
}

clock clock::minus(std::int32_t minutes) const noexcept {
    const std::int32_t total = (minutes_ - minutes);
    return clock(total);
}

std::string clock::to_string() const {
    const std::int32_t hour = (minutes_ / minutes_per_hour);
    const std::int32_t minute = (minutes_ % minutes_per_hour);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hour
        << ':' << std::setfill('0') << std::setw(2) << minute;
    return oss.str();
}

clock::operator std::string() const {
    return this->to_string();
}

bool operator==(const clock& lhs, const clock& rhs) noexcept {
    return (lhs.minutes_ == rhs.minutes_);
}

bool operator!=(const clock& lhs, const clock& rhs) noexcept {
    return (lhs.minutes_ != rhs.minutes_);
}

}  // namespace date_independent
