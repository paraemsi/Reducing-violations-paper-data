#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

namespace {
constexpr std::int32_t minutes_per_hour = static_cast<std::int32_t>(60);
constexpr std::int32_t hours_per_day = static_cast<std::int32_t>(24);
constexpr std::int32_t minutes_per_day = static_cast<std::int32_t>((minutes_per_hour * hours_per_day));

std::int32_t normalize(std::int32_t total_minutes) {
    std::int32_t m = (total_minutes % minutes_per_day);
    if ((m < 0)) {
        m = (m + minutes_per_day);
    }
    return m;
}
}  // unnamed namespace

clock clock::at(std::int32_t hour, std::int32_t minute) {
    std::int32_t total = ((hour * minutes_per_hour) + minute);
    return clock(normalize(total));
}

clock clock::at(std::int32_t hour) {
    return clock::at(hour, static_cast<std::int32_t>(0));
}

clock at(std::int32_t hour, std::int32_t minute) {
    return clock::at(hour, minute);
}

clock at(std::int32_t hour) {
    return clock::at(hour);
}

clock::clock(std::int32_t total_minutes)
    : minutes_since_midnight(normalize(total_minutes)) {
}

clock clock::plus(std::int32_t minutes) const {
    std::int32_t total = (minutes_since_midnight + minutes);
    return clock(normalize(total));
}

std::string clock::to_string() const {
    std::int32_t hours = (minutes_since_midnight / minutes_per_hour);
    std::int32_t mins = (minutes_since_midnight % minutes_per_hour);

    std::ostringstream oss;
    oss << std::setw(2)
        << std::setfill('0')
        << hours
        << ':'
        << std::setw(2)
        << std::setfill('0')
        << mins;
    return oss.str();
}

std::string clock::str() const {
    return to_string();
}

clock::operator std::string() const {
    return to_string();
}

bool operator==(const clock& lhs, const clock& rhs) {
    return (lhs.minutes_since_midnight == rhs.minutes_since_midnight);
}

bool operator!=(const clock& lhs, const clock& rhs) {
    return (lhs.minutes_since_midnight != rhs.minutes_since_midnight);
}

}  // namespace date_independent
