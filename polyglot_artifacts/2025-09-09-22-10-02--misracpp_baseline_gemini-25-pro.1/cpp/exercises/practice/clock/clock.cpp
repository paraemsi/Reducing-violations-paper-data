#include "clock.h"

#include <iomanip>
#include <sstream>
#include <string>

namespace date_independent {

namespace {
const int kMinutesPerDay = 24 * 60;
const int kMinutesPerHour = 60;
}  // namespace

clock clock::at(int hours, int minutes) {
    return clock(hours * kMinutesPerHour + minutes);
}

clock::clock(int minutes) {
    minutes_ = minutes % kMinutesPerDay;
    if (minutes_ < 0) {
        minutes_ += kMinutesPerDay;
    }
}

clock clock::operator+(int minutes) const {
    return clock(minutes_ + minutes);
}

clock clock::operator-(int minutes) const {
    return clock(minutes_ - minutes);
}


clock::operator std::string() const {
    const int hours = minutes_ / kMinutesPerHour;
    const int minutes = minutes_ % kMinutesPerHour;

    std::ostringstream stream;
    stream << std::setw(2) << std::setfill('0') << hours << ":"
           << std::setw(2) << std::setfill('0') << minutes;
    return stream.str();
}

}  // namespace date_independent
