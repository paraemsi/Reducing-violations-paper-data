#include "space_age.h"
#include <cmath>

namespace space_age {

space_age::space_age(age_seconds_t seconds) : age_seconds(seconds) {}

age_seconds_t space_age::seconds() const {
    return age_seconds;
}

double space_age::on_earth() const {
    constexpr double earth_seconds_per_year = 31557600.0;
    return (static_cast<double>(age_seconds)) / earth_seconds_per_year;
}

double space_age::on_mercury() const {
    constexpr double orbital_period = 0.2408467;
    return (on_earth()) / orbital_period;
}

double space_age::on_venus() const {
    constexpr double orbital_period = 0.61519726;
    return (on_earth()) / orbital_period;
}

double space_age::on_mars() const {
    constexpr double orbital_period = 1.8808158;
    return (on_earth()) / orbital_period;
}

double space_age::on_jupiter() const {
    constexpr double orbital_period = 11.862615;
    return (on_earth()) / orbital_period;
}

double space_age::on_saturn() const {
    constexpr double orbital_period = 29.447498;
    return (on_earth()) / orbital_period;
}

double space_age::on_uranus() const {
    constexpr double orbital_period = 84.016846;
    return (on_earth()) / orbital_period;
}

double space_age::on_neptune() const {
    constexpr double orbital_period = 164.79132;
    return (on_earth()) / orbital_period;
}

}  // namespace space_age
