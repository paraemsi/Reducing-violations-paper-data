#include "space_age.h"

namespace {
    // Constants for orbital periods relative to Earth years
    constexpr double seconds_per_earth_year = 31557600.0;

    constexpr double mercury_orbital_period = 0.2408467;
    constexpr double venus_orbital_period   = 0.61519726;
    constexpr double mars_orbital_period    = 1.8808158;
    constexpr double jupiter_orbital_period = 11.862615;
    constexpr double saturn_orbital_period  = 29.447498;
    constexpr double uranus_orbital_period  = 84.016846;
    constexpr double neptune_orbital_period = 164.79132;
}  // unnamed namespace

namespace space_age {

space_age::space_age(std::uint64_t seconds) noexcept
    : seconds_{seconds} {}

std::uint64_t space_age::seconds() const noexcept {
    return seconds_;
}

double space_age::earth_years() const noexcept {
    // Convert stored seconds to Earth years
    return (static_cast<double>(seconds_) / seconds_per_earth_year);
}

double space_age::on_earth() const noexcept {
    return earth_years();
}

double space_age::on_mercury() const noexcept {
    return (earth_years() / mercury_orbital_period);
}

double space_age::on_venus() const noexcept {
    return (earth_years() / venus_orbital_period);
}

double space_age::on_mars() const noexcept {
    return (earth_years() / mars_orbital_period);
}

double space_age::on_jupiter() const noexcept {
    return (earth_years() / jupiter_orbital_period);
}

double space_age::on_saturn() const noexcept {
    return (earth_years() / saturn_orbital_period);
}

double space_age::on_uranus() const noexcept {
    return (earth_years() / uranus_orbital_period);
}

double space_age::on_neptune() const noexcept {
    return (earth_years() / neptune_orbital_period);
}

}  // namespace space_age
