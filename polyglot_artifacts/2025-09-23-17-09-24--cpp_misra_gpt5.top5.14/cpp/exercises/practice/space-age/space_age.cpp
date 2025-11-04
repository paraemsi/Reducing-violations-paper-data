#include "space_age.h"

namespace {
    constexpr double k_earth_year_seconds = 31557600.0;
    constexpr double k_mercury_period = 0.2408467;
    constexpr double k_venus_period = 0.61519726;
    constexpr double k_earth_period = 1.0;
    constexpr double k_mars_period = 1.8808158;
    constexpr double k_jupiter_period = 11.862615;
    constexpr double k_saturn_period = 29.447498;
    constexpr double k_uranus_period = 84.016846;
    constexpr double k_neptune_period = 164.79132;
}

namespace space_age {

space_age::space_age(double seconds) noexcept
    : seconds_{seconds} {}

double space_age::seconds() const noexcept {
    return seconds_;
}

double space_age::on_planet(double orbital_period_in_earth_years) const noexcept {
    return (seconds_) / ((k_earth_year_seconds) * (orbital_period_in_earth_years));
}

double space_age::on_mercury() const noexcept {
    return on_planet(k_mercury_period);
}

double space_age::on_venus() const noexcept {
    return on_planet(k_venus_period);
}

double space_age::on_earth() const noexcept {
    return on_planet(k_earth_period);
}

double space_age::on_mars() const noexcept {
    return on_planet(k_mars_period);
}

double space_age::on_jupiter() const noexcept {
    return on_planet(k_jupiter_period);
}

double space_age::on_saturn() const noexcept {
    return on_planet(k_saturn_period);
}

double space_age::on_uranus() const noexcept {
    return on_planet(k_uranus_period);
}

double space_age::on_neptune() const noexcept {
    return on_planet(k_neptune_period);
}

}  // namespace space_age
