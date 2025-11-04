#include "space_age.h"

namespace space_age {

namespace {
    // Orbital periods relative to Earth years
    constexpr double mercury_period = 0.2408467;
    constexpr double venus_period   = 0.61519726;
    constexpr double earth_period   = 1.0;
    constexpr double mars_period    = 1.8808158;
    constexpr double jupiter_period = 11.862615;
    constexpr double saturn_period  = 29.447498;
    constexpr double uranus_period  = 84.016846;
    constexpr double neptune_period = 164.79132;
}  // namespace

space_age::space_age(std::uint64_t seconds) noexcept
    : seconds_{seconds} {}

std::uint64_t space_age::seconds() const noexcept {
    return seconds_;
}

double space_age::on_planet(double orbital_period) const noexcept {
    // Age on a planet = seconds / (Earth seconds per year * orbital period)
    return (static_cast<double>(seconds_) / (earth_year_seconds * orbital_period));
}

double space_age::on_earth() const noexcept {
    return (static_cast<double>(seconds_) / (earth_year_seconds * earth_period));
}

double space_age::on_mercury() const noexcept {
    return on_planet(mercury_period);
}

double space_age::on_venus() const noexcept {
    return on_planet(venus_period);
}

double space_age::on_mars() const noexcept {
    return on_planet(mars_period);
}

double space_age::on_jupiter() const noexcept {
    return on_planet(jupiter_period);
}

double space_age::on_saturn() const noexcept {
    return on_planet(saturn_period);
}

double space_age::on_uranus() const noexcept {
    return on_planet(uranus_period);
}

double space_age::on_neptune() const noexcept {
    return on_planet(neptune_period);
}

}  // namespace space_age
