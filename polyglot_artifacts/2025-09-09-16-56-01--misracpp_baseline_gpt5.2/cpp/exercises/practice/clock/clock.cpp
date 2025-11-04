#include "clock.h"

#include <iomanip>
#include <sstream>

namespace date_independent {

namespace {
constexpr int kMinutesPerDay = 24 * 60;
}

int clock::normalize(int minutes) noexcept {
    int m = minutes % kMinutesPerDay;
    if (m < 0) m += kMinutesPerDay;
    return m;
}

clock::clock(int total_minutes) noexcept
    : mins_{normalize(total_minutes)} {}

clock clock::at(int hour, int minute) noexcept {
    return clock(hour * 60 + minute);
}

clock clock::plus(int minutes) const noexcept {
    return clock(mins_ + minutes);
}

clock clock::minus(int minutes) const noexcept {
    return clock(mins_ - minutes);
}

std::string clock::str() const {
    int hours = mins_ / 60;
    int minutes = mins_ % 60;

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hours
        << ':' << std::setw(2) << minutes;
    return oss.str();
}

}  // namespace date_independent
