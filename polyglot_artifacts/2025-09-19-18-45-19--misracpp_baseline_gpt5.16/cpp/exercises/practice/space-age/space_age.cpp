#include "space_age.h"
#include <cmath>

namespace space_age {

namespace {
    constexpr double earth_year_seconds = 31557600.0;

    // Orbital period relative to Earth years
    constexpr double mercury_period = 0.2408467;
    constexpr double venus_period   = 0.61519726;
    constexpr double earth_period   = 1.0;
    constexpr double mars_period    = 1.8808158;
    constexpr double jupiter_period = 11.862615;
    constexpr double saturn_period  = 29.447498;
    constexpr double uranus_period  = 84.016846;
    constexpr double neptune_period = 164.79132;
}

space_age::space_age(long long seconds)
    : seconds_{seconds} {}

long long space_age::seconds() const {
    return seconds_;
}

double space_age::on_earth() const {
    const double years = seconds_ / (earth_year_seconds * earth_period);
    return std::round(years * 100.0) / 100.0;
}

double space_age::on_mercury() const {
    const double years = seconds_ / (earth_year_seconds * mercury_period);
    return std::round(years * 100.0) / 100.0;
}

double space_age::on_venus() const {
    const double years = seconds_ / (earth_year_seconds * venus_period);
    return std::round(years * 100.0) / 100.0;
}

double space_age::on_mars() const {
    const double years = seconds_ / (earth_year_seconds * mars_period);
    return std::round(years * 100.0) / 100.0;
}

double space_age::on_jupiter() const {
    const double years = seconds_ / (earth_year_seconds * jupiter_period);
    return std::round(years * 100.0) / 100.0;
}

double space_age::on_saturn() const {
    const double years = seconds_ / (earth_year_seconds * saturn_period);
    return std::round(years * 100.0) / 100.0;
}

double space_age::on_uranus() const {
    const double years = seconds_ / (earth_year_seconds * uranus_period);
    return std::round(years * 100.0) / 100.0;
}

double space_age::on_neptune() const {
    const double years = seconds_ / (earth_year_seconds * neptune_period);
    return std::round(years * 100.0) / 100.0;
}

}  // namespace space_age
