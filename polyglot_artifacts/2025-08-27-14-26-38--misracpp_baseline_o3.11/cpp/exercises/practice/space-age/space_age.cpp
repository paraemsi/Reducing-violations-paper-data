#include "space_age.h"

namespace space_age {

space_age::space_age(unsigned long long seconds) : seconds_{seconds} {}

unsigned long long space_age::seconds() const {
    return seconds_;
}

double space_age::age_on_planet(double orbital_period_factor) const {
    return static_cast<double>(seconds_) / (earth_year_seconds * orbital_period_factor);
}

double space_age::on_earth() const {
    return age_on_planet(1.0);
}

double space_age::on_mercury() const {
    return age_on_planet(mercury_factor);
}

double space_age::on_venus() const {
    return age_on_planet(venus_factor);
}

double space_age::on_mars() const {
    return age_on_planet(mars_factor);
}

double space_age::on_jupiter() const {
    return age_on_planet(jupiter_factor);
}

double space_age::on_saturn() const {
    return age_on_planet(saturn_factor);
}

double space_age::on_uranus() const {
    return age_on_planet(uranus_factor);
}

double space_age::on_neptune() const {
    return age_on_planet(neptune_factor);
}

}  // namespace space_age
