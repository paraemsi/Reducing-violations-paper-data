#include "space_age.h"

namespace space_age {

constexpr double space_age::earth_year_seconds;
constexpr double space_age::mercury_period;
constexpr double space_age::venus_period;
constexpr double space_age::earth_period;
constexpr double space_age::mars_period;
constexpr double space_age::jupiter_period;
constexpr double space_age::saturn_period;
constexpr double space_age::uranus_period;
constexpr double space_age::neptune_period;

space_age::space_age(long long seconds)
    : seconds_{seconds} {}

long long space_age::seconds() const {
    return seconds_;
}

double space_age::on_planet(double orbital_period) const {
    return seconds_ / (earth_year_seconds * orbital_period);
}

double space_age::on_earth() const { return on_planet(earth_period); }
double space_age::on_mercury() const { return on_planet(mercury_period); }
double space_age::on_venus() const { return on_planet(venus_period); }
double space_age::on_mars() const { return on_planet(mars_period); }
double space_age::on_jupiter() const { return on_planet(jupiter_period); }
double space_age::on_saturn() const { return on_planet(saturn_period); }
double space_age::on_uranus() const { return on_planet(uranus_period); }
double space_age::on_neptune() const { return on_planet(neptune_period); }

}  // namespace space_age
