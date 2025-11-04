#include "clock.h"
#include <iomanip>
#include <sstream>
#include <ostream>

namespace date_independent {

static constexpr std::int32_t HOURS_PER_DAY = static_cast<std::int32_t>(24);
static constexpr std::int32_t MINUTES_PER_HOUR = static_cast<std::int32_t>(60);
static constexpr std::int32_t MINUTES_PER_DAY = (HOURS_PER_DAY * MINUTES_PER_HOUR);

clock::clock(std::int32_t minute_of_day) noexcept
    : m_minute_of_day(normalize(minute_of_day)) {
}

std::int32_t clock::normalize(std::int32_t total_minutes) noexcept {
    std::int32_t result = (total_minutes % MINUTES_PER_DAY);
    if ((result < static_cast<std::int32_t>(0))) {
        result = (result + MINUTES_PER_DAY);
    }
    return result;
}

clock clock::at(std::int32_t hour, std::int32_t minute) noexcept {
    std::int32_t total = ((hour * MINUTES_PER_HOUR) + minute);
    return clock(total);
}

clock clock::plus(std::int32_t minutes) const noexcept {
    std::int32_t total = (m_minute_of_day + minutes);
    return clock(total);
}

clock clock::minus(std::int32_t minutes) const noexcept {
    std::int32_t total = (m_minute_of_day - minutes);
    return clock(total);
}

clock::operator std::string() const {
    std::int32_t hours = (m_minute_of_day / MINUTES_PER_HOUR);
    std::int32_t minutes = (m_minute_of_day % MINUTES_PER_HOUR);

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours
        << ":" << std::setw(2) << std::setfill('0') << minutes;
    return oss.str();
}

bool operator==(const clock& lhs, const clock& rhs) noexcept {
    return (lhs.m_minute_of_day == rhs.m_minute_of_day);
}

bool operator!=(const clock& lhs, const clock& rhs) noexcept {
    return (!(lhs == rhs));
}

std::ostream& operator<<(std::ostream& os, const clock& rhs) {
    const std::string s = static_cast<std::string>(rhs);
    os << s;
    return os;
}

}  // namespace date_independent
