#include "space_age.h"

namespace {
    constexpr double seconds_per_earth_year = 31557600.0;
    constexpr double orbital_mercury = 0.2408467;
    constexpr double orbital_venus = 0.61519726;
    constexpr double orbital_earth = 1.0;
    constexpr double orbital_mars = 1.8808158;
    constexpr double orbital_jupiter = 11.862615;
    constexpr double orbital_saturn = 29.447498;
    constexpr double orbital_uranus = 84.016846;
    constexpr double orbital_neptune = 164.79132;
}

namespace space_age {

space_age::space_age(std::uint64_t seconds) noexcept : m_seconds(seconds) {}

std::uint64_t space_age::seconds() const noexcept {
    return m_seconds;
}

static double compute_on_planet(std::uint64_t seconds, double orbital_period) noexcept {
    const double seconds_d = static_cast<double>(seconds);
    return (seconds_d / (seconds_per_earth_year * orbital_period));
}

double space_age::on_earth() const noexcept {
    return (compute_on_planet(m_seconds, orbital_earth));
}

double space_age::on_mercury() const noexcept {
    return (compute_on_planet(m_seconds, orbital_mercury));
}

double space_age::on_venus() const noexcept {
    return (compute_on_planet(m_seconds, orbital_venus));
}

double space_age::on_mars() const noexcept {
    return (compute_on_planet(m_seconds, orbital_mars));
}

double space_age::on_jupiter() const noexcept {
    return (compute_on_planet(m_seconds, orbital_jupiter));
}

double space_age::on_saturn() const noexcept {
    return (compute_on_planet(m_seconds, orbital_saturn));
}

double space_age::on_uranus() const noexcept {
    return (compute_on_planet(m_seconds, orbital_uranus));
}

double space_age::on_neptune() const noexcept {
    return (compute_on_planet(m_seconds, orbital_neptune));
}

}  // namespace space_age
