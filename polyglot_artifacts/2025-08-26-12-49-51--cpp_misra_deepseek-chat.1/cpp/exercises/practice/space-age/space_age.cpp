#include "space_age.h"
#include <cmath>

namespace space_age {

space_age::space_age(double seconds) : age_in_seconds_(seconds) {}

double space_age::seconds() const {
    return age_in_seconds_;
}

double space_age::on_earth() const {
    constexpr double earth_seconds_per_year = 31557600.0;
    return age_in_seconds_ / earth_seconds_per_year;
}

double space_age::on_mercury() const {
    constexpr double mercury_orbital_period = 0.2408467;
    return on_earth() / mercury_orbital_period;
}

double space_age::on_venus() const {
    constexpr double venus_orbital_period = 0.61519726;
    return on_earth() / venus_orbital_period;
}

double space_age::on_mars() const {
    constexpr double mars_orbital_period = 1.8808158;
    return on_earth() / mars_orbital_period;
}

double space_age::on_jupiter() const {
    constexpr double jupiter_orbital_period = 11.862615;
    return on_earth() / jupiter_orbital_period;
}

double space_age::on_saturn() const {
    constexpr double saturn_orbital_period = 29.447498;
    return on_earth() / saturn_orbital_period;
}

double space_age::on_uranus() const {
    constexpr double uranus_orbital_period = 84.016846;
    return on_earth() / uranus_orbital_period;
}

double space_age::on_neptune() const {
    constexpr double neptune_orbital_period = 164.79132;
    return on_earth() / neptune_orbital_period;
}

}  // namespace space_age
