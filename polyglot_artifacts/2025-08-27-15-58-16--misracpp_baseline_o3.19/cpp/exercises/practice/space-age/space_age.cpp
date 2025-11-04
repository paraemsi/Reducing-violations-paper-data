#include "space_age.h"

namespace space_age {

// Define the static class member.
constexpr double space_age::earth_year_seconds;

space_age::space_age(int64_t seconds) : m_seconds(seconds) {}

int64_t space_age::seconds() const {
    return m_seconds;
}

double space_age::on_earth() const {
    return m_seconds / earth_year_seconds;
}

double space_age::on_mercury() const {
    return on_earth() / 0.2408467;
}

double space_age::on_venus() const {
    return on_earth() / 0.61519726;
}

double space_age::on_mars() const {
    return on_earth() / 1.8808158;
}

double space_age::on_jupiter() const {
    return on_earth() / 11.862615;
}

double space_age::on_saturn() const {
    return on_earth() / 29.447498;
}

double space_age::on_uranus() const {
    return on_earth() / 84.016846;
}

double space_age::on_neptune() const {
    return on_earth() / 164.79132;
}

}  // namespace space_age
