#include "clock.h"

#include <cstdint>
#include <iomanip>
#include <sstream>

namespace {
    constexpr std::int32_t kMinutesPerHour = static_cast<std::int32_t>(60);
    constexpr std::int32_t kHoursPerDay = static_cast<std::int32_t>(24);
    constexpr std::int32_t kMinutesPerDay = (kHoursPerDay * kMinutesPerHour);
}

namespace date_independent {

clock clock::at(std::int32_t hour, std::int32_t minute) {
    const std::int32_t total = ((hour * kMinutesPerHour) + minute);
    const std::int32_t normalized = clock::normalize_total_minutes(total);
    return clock(normalized);
}

clock clock::plus(std::int32_t minute_delta) const {
    const std::int32_t sum = (total_minutes_ + minute_delta);
    const std::int32_t normalized = clock::normalize_total_minutes(sum);
    return clock(normalized);
}

clock::operator std::string() const {
    const std::int32_t hour = (total_minutes_ / kMinutesPerHour);
    const std::int32_t minute = (total_minutes_ % kMinutesPerHour);

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hour;
    oss << ":";
    oss << std::setw(2) << std::setfill('0') << minute;
    return oss.str();
}

bool operator==(const clock& lhs, const clock& rhs) noexcept {
    return (lhs.total_minutes_ == rhs.total_minutes_);
}

bool operator!=(const clock& lhs, const clock& rhs) noexcept {
    return (lhs.total_minutes_ != rhs.total_minutes_);
}

std::int32_t clock::normalize_total_minutes(std::int32_t total_minutes) noexcept {
    const std::int32_t mod = (total_minutes % kMinutesPerDay);
    const std::int32_t normalized = ((mod + kMinutesPerDay) % kMinutesPerDay);
    return normalized;
}

clock::clock(std::int32_t total_minutes)
    : total_minutes_(clock::normalize_total_minutes(total_minutes)) {
}

}  // namespace date_independent
