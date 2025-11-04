#include "space_age.h"

namespace space_age {

space_age::space_age(long long seconds) : age_in_seconds(seconds) {
}

long long space_age::seconds() const {
    return age_in_seconds;
}

double space_age::on_mercury() const {
    return (age_in_seconds / seconds_per_earth_year) / mercury_orbital_period;
}

double space_age::on_venus() const {
    return (age_in_seconds / seconds_per_earth_year) / venus_orbital_period;
}

double space_age::on_earth() const {
    return age_in_seconds / seconds_per_earth_year;
}

double space_age::on_mars() const {
    return (age_in_seconds / seconds_per_earth_year) / mars_orbital_period;
}

double space_age::on_jupiter() const {
    return (age_in_seconds / seconds_per_earth_year) / jupiter_orbital_period;
}

double space_age::on_saturn() const {
    return (age_in_seconds / seconds_per_earth_year) / saturn_orbital_period;
}

double space_age::on_uranus() const {
    return (age_in_seconds / seconds_per_earth_year) / uranus_orbital_period;
}

double space_age::on_neptune() const {
    return (age_in_seconds / seconds_per_earth_year) / neptune_orbital_period;
}

}  // namespace space_age
