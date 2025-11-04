#include "space_age.h"

namespace space_age {

space_age::space_age(std::uint64_t seconds_in) : seconds_(seconds_in) { }

std::uint64_t space_age::seconds() const {
    return seconds_;
}

double space_age::age_on_planet(double orbital_period) const {
    return (static_cast<double>(seconds_) / earth_year_in_seconds) / orbital_period;
}

double space_age::on_earth() const {
    return age_on_planet(1.0);
}

double space_age::on_mercury() const {
    return age_on_planet(mercury_orbital);
}

double space_age::on_venus() const {
    return age_on_planet(venus_orbital);
}

double space_age::on_mars() const {
    return age_on_planet(mars_orbital);
}

double space_age::on_jupiter() const {
    return age_on_planet(jupiter_orbital);
}

double space_age::on_saturn() const {
    return age_on_planet(saturn_orbital);
}

double space_age::on_uranus() const {
    return age_on_planet(uranus_orbital);
}

double space_age::on_neptune() const {
    return age_on_planet(neptune_orbital);
}

}  // namespace space_age
