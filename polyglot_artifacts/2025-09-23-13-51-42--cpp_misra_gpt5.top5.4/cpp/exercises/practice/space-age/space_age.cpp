#include "space_age.h"

namespace space_age {

space_age::space_age(seconds_type seconds) noexcept
    : seconds_(seconds) {
}

space_age::seconds_type space_age::seconds() const noexcept {
    return seconds_;
}

double space_age::on_planet(double orbital_period_in_earth_years) const noexcept {
    const double denominator = (seconds_per_earth_year * orbital_period_in_earth_years);
    return (static_cast<double>(seconds_) / denominator);
}

double space_age::on_earth() const noexcept {
    return on_planet(earth_orbital_years);
}

double space_age::on_mercury() const noexcept {
    return on_planet(mercury_orbital_years);
}

double space_age::on_venus() const noexcept {
    return on_planet(venus_orbital_years);
}

double space_age::on_mars() const noexcept {
    return on_planet(mars_orbital_years);
}

double space_age::on_jupiter() const noexcept {
    return on_planet(jupiter_orbital_years);
}

double space_age::on_saturn() const noexcept {
    return on_planet(saturn_orbital_years);
}

double space_age::on_uranus() const noexcept {
    return on_planet(uranus_orbital_years);
}

double space_age::on_neptune() const noexcept {
    return on_planet(neptune_orbital_years);
}

}  // namespace space_age
