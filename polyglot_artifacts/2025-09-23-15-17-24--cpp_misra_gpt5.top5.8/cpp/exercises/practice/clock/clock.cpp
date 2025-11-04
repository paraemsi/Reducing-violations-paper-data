#include "clock.h"

#include <cstdint>
#include <iomanip>
#include <sstream>
#include <ostream>

namespace date_independent {

namespace {
    // Constants kept in an unnamed namespace for internal linkage
    static constexpr std::int32_t MINUTES_PER_HOUR = 60;
    static constexpr std::int32_t HOURS_PER_DAY = 24;
    static constexpr std::int32_t MINUTES_PER_DAY = (HOURS_PER_DAY * MINUTES_PER_HOUR);
}

clock::clock(std::int32_t total_minutes)
    : total_minutes_(clock::normalize(total_minutes)) {
}

std::int32_t clock::normalize(std::int32_t total_minutes) {
    std::int32_t mod = (total_minutes % MINUTES_PER_DAY);
    if ((mod < 0)) {
        mod = (mod + MINUTES_PER_DAY);
    }
    return mod;
}

clock clock::at(std::int32_t hours, std::int32_t minutes) {
    std::int32_t total = ((hours * MINUTES_PER_HOUR) + minutes);
    return clock(total);
}

clock clock::plus(std::int32_t minutes) const {
    return clock((total_minutes_ + minutes));
}

clock clock::minus(std::int32_t minutes) const {
    return clock((total_minutes_ - minutes));
}

std::string clock::str() const {
    std::int32_t hours = (total_minutes_ / MINUTES_PER_HOUR);
    std::int32_t minutes = (total_minutes_ % MINUTES_PER_HOUR);

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours
        << ':'
        << std::setw(2) << std::setfill('0') << minutes;
    return oss.str();
}

clock::operator std::string() const {
    return this->str();
}

bool clock::operator==(const clock& other) const {
    return (total_minutes_ == other.total_minutes_);
}

bool clock::operator!=(const clock& other) const {
    return (!(operator==(other)));
}

std::ostream& operator<<(std::ostream& os, const clock& c) {
    os << static_cast<std::string>(c);
    return os;
}

}  // namespace date_independent
