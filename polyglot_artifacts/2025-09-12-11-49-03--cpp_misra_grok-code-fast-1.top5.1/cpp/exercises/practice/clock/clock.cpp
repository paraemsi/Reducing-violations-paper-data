#include "clock.h"

namespace date_independent {

clock clock::at(std::int32_t hour, std::int32_t minute) {
    return clock(hour, minute);
}

clock::clock(std::int32_t hours, std::int32_t minutes) {
    std::int32_t total = ((hours * 60) + minutes);
    while (total < 0) {
        total += 1440;
    }
    total_minutes = (total % 1440);
}

clock clock::plus(std::int32_t minutes) const {
    std::int32_t new_total = (total_minutes + minutes);
    while (new_total < 0) {
        new_total += 1440;
    }
    clock result(0, 0);
    result.total_minutes = (new_total % 1440);
    return result;
}

clock clock::minus(std::int32_t minutes) const {
    std::int32_t new_total = (total_minutes - minutes);
    while (new_total < 0) {
        new_total += 1440;
    }
    clock result(0, 0);
    result.total_minutes = (new_total % 1440);
    return result;
}

bool clock::operator==(const clock& other) const {
    return (total_minutes == other.total_minutes);
}

std::int32_t clock::get_hours() const {
    return (total_minutes / 60);
}

std::int32_t clock::get_minutes() const {
    return (total_minutes % 60);
}

}  // namespace date_independent
