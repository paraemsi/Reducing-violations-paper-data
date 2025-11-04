#include "space_age.h"

namespace {

constexpr double earth_year_in_seconds = 31557600.0;
constexpr double mercury_orbital_period = 0.2408467;
constexpr double venus_orbital_period = 0.61519726;
constexpr double mars_orbital_period = 1.8808158;
constexpr double jupiter_orbital_period = 11.862615;
constexpr double saturn_orbital_period = 29.447498;
constexpr double uranus_orbital_period = 84.016846;
constexpr double neptune_orbital_period = 164.79132;

} // anonymous namespace

namespace space_age {

space_age::space_age(std::int64_t age_in_seconds) noexcept : age_in_seconds_{age_in_seconds} {
}

std::int64_t space_age::seconds() const noexcept {
    return age_in_seconds_;
}

double space_age::on_earth() const noexcept {
    return (static_cast<double>(age_in_seconds_) / earth_year_in_seconds);
}

double space_age::on_mercury() const noexcept {
    return (on_earth() / mercury_orbital_period);
}

double space_age::on_venus() const noexcept {
    return (on_earth() / venus_orbital_period);
}

double space_age::on_mars() const noexcept {
    return (on_earth() / mars_orbital_period);
}

double space_age::on_jupiter() const noexcept {
    return (on_earth() / jupiter_orbital_period);
}

double space_age::on_saturn() const noexcept {
    return (on_earth() / saturn_orbital_period);
}

double space_age::on_uranus() const noexcept {
    return (on_earth() / uranus_orbital_period);
}

double space_age::on_neptune() const noexcept {
    return (on_earth() / neptune_orbital_period);
}

}  // namespace space_age
