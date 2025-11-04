#include "space_age.h"
#include <cmath>

namespace space_age {

space_age::space_age(std::int64_t seconds) : age_seconds(seconds) {}

std::int64_t space_age::seconds() const {
    return age_seconds;
}

double space_age::on_mercury() const {
    constexpr double earth_years_per_second = (1.0 / 31557600.0);
    constexpr double mercury_orbital_period = 0.2408467;
    return (static_cast<double>(age_seconds) * earth_years_per_second) / mercury_orbital_period;
}

double space_age::on_venus() const {
    constexpr double earth_years_per_second = (1.0 / 31557600.0);
    constexpr double venus_orbital_period = 0.61519726;
    return (static_cast<double>(age_seconds) * earth_years_per_second) / venus_orbital_period;
}

double space_age::on_earth() const {
    constexpr double earth_years_per_second = (1.0 / 31557600.0);
    return (static_cast<double>(age_seconds) * earth_years_per_second);
}

double space_age::on_mars() const {
    constexpr double earth_years_per_second = (1.0 / 31557600.0);
    constexpr double mars_orbital_period = 1.8808158;
    return (static_cast<double>(age_seconds) * earth_years_per_second) / mars_orbital_period;
}

double space_age::on_jupiter() const {
    constexpr double earth_years_per_second = (1.0 / 31557600.0);
    constexpr double jupiter_orbital_period = 11.862615;
    return (static_cast<double>(age_seconds) * earth_years_per_second) / jupiter_orbital_period;
}

double space_age::on_saturn() const {
    constexpr double earth_years_per_second = (1.0 / 31557600.0);
    constexpr double saturn_orbital_period = 29.447498;
    return (static_cast<double>(age_seconds) * earth_years_per_second) / saturn_orbital_period;
}

double space_age::on_uranus() const {
    constexpr double earth_years_per_second = (1.0 / 31557600.0);
    constexpr double uranus_orbital_period = 84.016846;
    return (static_cast<double>(age_seconds) * earth_years_per_second) / uranus_orbital_period;
}

double space_age::on_neptune() const {
    constexpr double earth_years_per_second = (1.0 / 31557600.0);
    constexpr double neptune_orbital_period = 164.79132;
    return (static_cast<double>(age_seconds) * earth_years_per_second) / neptune_orbital_period;
}

}  // namespace space_age
