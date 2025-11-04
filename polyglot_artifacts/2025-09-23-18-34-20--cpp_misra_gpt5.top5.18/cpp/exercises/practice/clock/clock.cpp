#include "clock.h"

#include <cstdint>
#include <iomanip>
#include <sstream>

namespace date_independent {

namespace {
constexpr std::int64_t day_minutes64 = (static_cast<std::int64_t>(24) * static_cast<std::int64_t>(60));

std::int32_t normalize_minutes64(std::int64_t minutes) {
    std::int64_t m = static_cast<std::int64_t>(minutes % day_minutes64);
    if ((m < static_cast<std::int64_t>(0))) {
        m = static_cast<std::int64_t>(m + day_minutes64);
    }
    return static_cast<std::int32_t>(m);
}
}  // namespace

clock::clock(minutes_t hour, minutes_t minute)
    : minutes_since_midnight_(normalize_minutes64((static_cast<std::int64_t>(hour) * static_cast<std::int64_t>(60)) + static_cast<std::int64_t>(minute))) {
}

clock clock::at(minutes_t hour, minutes_t minute) {
    return clock(hour, minute);
}

clock clock::plus(minutes_t minute) const {
    std::int64_t sum = static_cast<std::int64_t>(minutes_since_midnight_) + static_cast<std::int64_t>(minute);
    return clock(static_cast<minutes_t>(0), static_cast<minutes_t>(normalize_minutes64(sum)));
}

clock clock::minus(minutes_t minute) const {
    std::int64_t diff = static_cast<std::int64_t>(minutes_since_midnight_) - static_cast<std::int64_t>(minute);
    return clock(static_cast<minutes_t>(0), static_cast<minutes_t>(normalize_minutes64(diff)));
}

std::string clock::to_string() const {
    std::int32_t hours = static_cast<std::int32_t>(minutes_since_midnight_ / static_cast<std::int32_t>(60));
    std::int32_t minutes = static_cast<std::int32_t>(minutes_since_midnight_ % static_cast<std::int32_t>(60));

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours << ":" << std::setw(2) << std::setfill('0') << minutes;
    return oss.str();
}

clock::operator std::string() const {
    return to_string();
}

bool clock::operator==(const clock& rhs) const {
    return (minutes_since_midnight_ == rhs.minutes_since_midnight_);
}

bool clock::operator!=(const clock& rhs) const {
    return (minutes_since_midnight_ != rhs.minutes_since_midnight_);
}

}  // namespace date_independent
