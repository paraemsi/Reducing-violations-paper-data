#include "space_age.h"

namespace space_age {

namespace {
    constexpr double earth_year_seconds = 31557600.0;
    constexpr double mercury_orbital_period = 0.2408467;
    constexpr double venus_orbital_period   = 0.61519726;
    constexpr double earth_orbital_period   = 1.0;
    constexpr double mars_orbital_period    = 1.8808158;
    constexpr double jupiter_orbital_period = 11.862615;
    constexpr double saturn_orbital_period  = 29.447498;
    constexpr double uranus_orbital_period  = 84.016846;
    constexpr double neptune_orbital_period = 164.79132;

    inline double on_planet(std::uint64_t seconds, double orbital_period) {
        return seconds / (earth_year_seconds * orbital_period);
    }
}

space_age::space_age(std::uint64_t seconds)
    : seconds_(seconds) {}

std::uint64_t space_age::seconds() const {
    return seconds_;
}

double space_age::on_earth() const {
    return on_planet(seconds_, earth_orbital_period);
}

double space_age::on_mercury() const {
    return on_planet(seconds_, mercury_orbital_period);
}

double space_age::on_venus() const {
    return on_planet(seconds_, venus_orbital_period);
}

double space_age::on_mars() const {
    return on_planet(seconds_, mars_orbital_period);
}

double space_age::on_jupiter() const {
    return on_planet(seconds_, jupiter_orbital_period);
}

double space_age::on_saturn() const {
    return on_planet(seconds_, saturn_orbital_period);
}

double space_age::on_uranus() const {
    return on_planet(seconds_, uranus_orbital_period);
}

double space_age::on_neptune() const {
    return on_planet(seconds_, neptune_orbital_period);
}

}  // namespace space_age
