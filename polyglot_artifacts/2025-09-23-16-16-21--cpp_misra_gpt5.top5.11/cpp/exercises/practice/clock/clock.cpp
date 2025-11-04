#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

namespace {
    static constexpr std::int32_t minutes_per_hour = 60;
    static constexpr std::int32_t minutes_per_day = (24 * 60);
}  // namespace

clock::clock(minute_type normalized_minutes) noexcept
    : minutes_since_midnight_(normalized_minutes) {}

clock clock::at(minute_type hour, minute_type minute) noexcept {
    const minute_type hours_per_day = (minutes_per_day / minutes_per_hour);
    const minute_type h_norm = (hour % hours_per_day);
    const minute_type m_norm = (minute % minutes_per_day);
    const minute_type total = (((h_norm * minutes_per_hour) + m_norm));
    return clock(normalize(total));
}

clock clock::plus(minute_type minutes) const noexcept {
    const minute_type delta = (minutes % minutes_per_day);
    const minute_type total = (minutes_since_midnight_ + delta);
    return clock(normalize(total));
}

clock clock::minus(minute_type minutes) const noexcept {
    const minute_type delta = (minutes % minutes_per_day);
    const minute_type total = (minutes_since_midnight_ - delta);
    return clock(normalize(total));
}

std::string clock::to_string() const {
    const minute_type hour = (minutes_since_midnight_ / minutes_per_hour);
    const minute_type minute = (minutes_since_midnight_ % minutes_per_hour);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hour << ':' << std::setw(2) << minute;
    return oss.str();
}

clock::operator std::string() const {
    return to_string();
}

bool operator==(const clock& lhs, const clock& rhs) noexcept {
    return (lhs.minutes_since_midnight_ == rhs.minutes_since_midnight_);
}

bool operator!=(const clock& lhs, const clock& rhs) noexcept {
    return (lhs.minutes_since_midnight_ != rhs.minutes_since_midnight_);
}

clock::minute_type clock::normalize(minute_type total_minutes) noexcept {
    minute_type result = (total_minutes % minutes_per_day);
    if (result < static_cast<minute_type>(0)) {
        result = (result + minutes_per_day);
    }
    return result;
}

}  // namespace date_independent
