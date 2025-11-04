#include "space_age.h"

namespace {

constexpr double seconds_per_earth_year = 31557600.0;

constexpr double mercury_period = 0.2408467;
constexpr double venus_period   = 0.61519726;
constexpr double earth_period   = 1.0;
constexpr double mars_period    = 1.8808158;
constexpr double jupiter_period = 11.862615;
constexpr double saturn_period  = 29.447498;
constexpr double uranus_period  = 84.016846;
constexpr double neptune_period = 164.79132;

}  // namespace

namespace space_age {

space_age::space_age(std::uint64_t seconds) noexcept
    : m_seconds(seconds) {}

std::uint64_t space_age::seconds() const noexcept {
    return m_seconds;
}

double space_age::on_planet(double orbital_period_in_earth_years) const noexcept {
    return (static_cast<double>(m_seconds) / (seconds_per_earth_year * orbital_period_in_earth_years));
}

double space_age::on_earth() const noexcept {
    return on_planet(earth_period);
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
