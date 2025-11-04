#include "clock.h"
#include <iomanip>
#include <sstream>

namespace date_independent {

clock::clock(int hour, int minute)
    : m_total_minutes(normalize(hour * 60 + minute)) {}

clock clock::at(int hour, int minute) {
    return clock(hour, minute);
}

int clock::normalize(int minutes) {
    const int minutes_in_day = 24 * 60;
    minutes %= minutes_in_day;
    if (minutes < 0) {
        minutes += minutes_in_day;
    }
    return minutes;
}

clock clock::plus(int minutes) const {
    return clock(0, m_total_minutes + minutes);
}

clock clock::minus(int minutes) const {
    return clock(0, m_total_minutes - minutes);
}

std::string clock::to_string() const {
    int hour = m_total_minutes / 60;
    int minute = m_total_minutes % 60;
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hour << ':'
        << std::setw(2) << std::setfill('0') << minute;
    return oss.str();
}

bool operator==(const clock& lhs, const clock& rhs) {
    return lhs.m_total_minutes == rhs.m_total_minutes;
}

bool operator!=(const clock& lhs, const clock& rhs) {
    return !(lhs == rhs);
}

clock::operator std::string() const {
    return to_string();
}

}  // namespace date_independent
