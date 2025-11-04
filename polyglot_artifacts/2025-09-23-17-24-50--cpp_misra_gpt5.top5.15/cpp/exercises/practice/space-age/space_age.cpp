#include "space_age.h"

namespace {
    constexpr double k_earth_year_seconds = 31557600.0;
    constexpr double k_mercury_period = 0.2408467;
    constexpr double k_venus_period   = 0.61519726;
    constexpr double k_mars_period    = 1.8808158;
    constexpr double k_jupiter_period = 11.862615;
    constexpr double k_saturn_period  = 29.447498;
    constexpr double k_uranus_period  = 84.016846;
    constexpr double k_neptune_period = 164.79132;
}  // unnamed namespace

namespace space_age {

space_age::space_age(space_age::seconds_t seconds) noexcept
    : seconds_{seconds} { }

space_age::seconds_t space_age::seconds() const noexcept {
    return seconds_;
}

space_age::real_t space_age::on_earth() const noexcept {
    return (static_cast<space_age::real_t>(seconds_) / k_earth_year_seconds);
}

space_age::real_t space_age::on_mercury() const noexcept {
    return (on_earth() / k_mercury_period);
}

space_age::real_t space_age::on_venus() const noexcept {
    return (on_earth() / k_venus_period);
}

space_age::real_t space_age::on_mars() const noexcept {
    return (on_earth() / k_mars_period);
}

space_age::real_t space_age::on_jupiter() const noexcept {
    return (on_earth() / k_jupiter_period);
}

space_age::real_t space_age::on_saturn() const noexcept {
    return (on_earth() / k_saturn_period);
}

space_age::real_t space_age::on_uranus() const noexcept {
    return (on_earth() / k_uranus_period);
}

space_age::real_t space_age::on_neptune() const noexcept {
    return (on_earth() / k_neptune_period);
}

}  // namespace space_age
