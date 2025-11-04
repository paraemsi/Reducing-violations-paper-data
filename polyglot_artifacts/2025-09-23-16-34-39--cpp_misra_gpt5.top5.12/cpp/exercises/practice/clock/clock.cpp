#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(std::int32_t total_minutes) noexcept
    : minutes_since_midnight_(normalize(total_minutes)) {
}

clock clock::at(std::int32_t hour, std::int32_t minute) noexcept {
    const std::int32_t total = ((hour * static_cast<std::int32_t>(60)) + minute);
    return clock(total);
}

clock clock::plus(std::int32_t minutes_delta) const noexcept {
    return clock((minutes_since_midnight_ + minutes_delta));
}

clock clock::minus(std::int32_t minutes_delta) const noexcept {
    return clock((minutes_since_midnight_ - minutes_delta));
}

std::string clock::to_string() const {
    const std::int32_t hours = (minutes_since_midnight_ / static_cast<std::int32_t>(60));
    const std::int32_t minutes = (minutes_since_midnight_ % static_cast<std::int32_t>(60));

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hours << ':' << std::setw(2) << minutes;
    return oss.str();
}

clock::operator std::string() const {
    return to_string();
}

std::int32_t clock::normalize(std::int32_t total_minutes) noexcept {
    std::int32_t m = (total_minutes % minutes_per_day);
    if (m < static_cast<std::int32_t>(0)) {
        m = (m + minutes_per_day);
    } else {
        // no operation
    }
    return m;
}

/* comparison operators are defined inline in the header */

}  // namespace date_independent
