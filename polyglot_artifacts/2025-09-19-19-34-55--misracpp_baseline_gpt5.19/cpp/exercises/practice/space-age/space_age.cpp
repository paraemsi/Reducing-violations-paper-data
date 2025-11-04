#include "space_age.h"

namespace space_age {

namespace {
    constexpr double earth_year_seconds = 31557600.0;

    constexpr double mercury_orbital = 0.2408467;
    constexpr double venus_orbital   = 0.61519726;
    constexpr double earth_orbital   = 1.0;
    constexpr double mars_orbital    = 1.8808158;
    constexpr double jupiter_orbital = 11.862615;
    constexpr double saturn_orbital  = 29.447498;
    constexpr double uranus_orbital  = 84.016846;
    constexpr double neptune_orbital = 164.79132;

    inline double age_on(long long seconds, double orbital_period) {
        return seconds / (earth_year_seconds * orbital_period);
    }
}

space_age::space_age(long long seconds)
    : seconds_(seconds) {}

long long space_age::seconds() const {
    return seconds_;
}

double space_age::on_earth() const {
    return age_on(seconds_, earth_orbital);
}

double space_age::on_mercury() const {
    return age_on(seconds_, mercury_orbital);
}

double space_age::on_venus() const {
    return age_on(seconds_, venus_orbital);
}

double space_age::on_mars() const {
    return age_on(seconds_, mars_orbital);
}

double space_age::on_jupiter() const {
    return age_on(seconds_, jupiter_orbital);
}

double space_age::on_saturn() const {
    return age_on(seconds_, saturn_orbital);
}

double space_age::on_uranus() const {
    return age_on(seconds_, uranus_orbital);
}

double space_age::on_neptune() const {
    return age_on(seconds_, neptune_orbital);
}

}  // namespace space_age
