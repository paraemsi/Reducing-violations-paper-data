#include "space_age.h"

namespace space_age {

space_age::space_age(long long seconds) : seconds_(seconds) {}

long long space_age::seconds() const {
    return seconds_;
}

double space_age::on_mercury() const {
    return (seconds_ / earth_seconds_per_year) / mercury_orbital_period;
}

double space_age::on_venus() const {
    return (seconds_ / earth_seconds_per_year) / venus_orbital_period;
}

double space_age::on_earth() const {
    return (seconds_ / earth_seconds_per_year) / earth_orbital_period;
}

double space_age::on_mars() const {
    return (seconds_ / earth_seconds_per_year) / mars_orbital_period;
}

double space_age::on_jupiter() const {
    return (seconds_ / earth_seconds_per_year) / jupiter_orbital_period;
}

double space_age::on_saturn() const {
    return (seconds_ / earth_seconds_per_year) / saturn_orbital_period;
}

double space_age::on_uranus() const {
    return (seconds_ / earth_seconds_per_year) / uranus_orbital_period;
}

double space_age::on_neptune() const {
    return (seconds_ / earth_seconds_per_year) / neptune_orbital_period;
}

}  // namespace space_age
