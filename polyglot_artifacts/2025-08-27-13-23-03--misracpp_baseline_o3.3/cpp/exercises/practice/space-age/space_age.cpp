#include "space_age.h"

namespace {

constexpr double earth_year_seconds = 31557600.0;

constexpr double mercury_factor = 0.2408467;
constexpr double venus_factor   = 0.61519726;
constexpr double mars_factor    = 1.8808158;
constexpr double jupiter_factor = 11.862615;
constexpr double saturn_factor  = 29.447498;
constexpr double uranus_factor  = 84.016846;
constexpr double neptune_factor = 164.79132;

}  // unnamed namespace

namespace space_age {

space_age::space_age(std::uint64_t seconds) : seconds_{seconds} {}

std::uint64_t space_age::seconds() const {
    return seconds_;
}

double space_age::on_planet(double orbital_factor) const {
    return static_cast<double>(seconds_) / (earth_year_seconds * orbital_factor);
}

double space_age::on_earth() const {
    return static_cast<double>(seconds_) / earth_year_seconds;
}

double space_age::on_mercury() const {
    return on_planet(mercury_factor);
}

double space_age::on_venus() const {
    return on_planet(venus_factor);
}

double space_age::on_mars() const {
    return on_planet(mars_factor);
}

double space_age::on_jupiter() const {
    return on_planet(jupiter_factor);
}

double space_age::on_saturn() const {
    return on_planet(saturn_factor);
}

double space_age::on_uranus() const {
    return on_planet(uranus_factor);
}

double space_age::on_neptune() const {
    return on_planet(neptune_factor);
}

}  // namespace space_age
