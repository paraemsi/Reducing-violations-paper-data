#include "space_age.h"

namespace {
constexpr double earth_year_seconds = 31557600.0;
}

namespace space_age {

space_age::space_age(long long total_seconds)
    : seconds_{total_seconds} {}

long long space_age::seconds() const {
    return seconds_;
}

double space_age::age_on(double orbital_period_in_earth_years) const {
    return static_cast<double>(seconds_) / (earth_year_seconds * orbital_period_in_earth_years);
}

double space_age::on_earth() const {
    return age_on(1.0);
}

double space_age::on_mercury() const {
    return age_on(0.2408467);
}

double space_age::on_venus() const {
    return age_on(0.61519726);
}

double space_age::on_mars() const {
    return age_on(1.8808158);
}

double space_age::on_jupiter() const {
    return age_on(11.862615);
}

double space_age::on_saturn() const {
    return age_on(29.447498);
}

double space_age::on_uranus() const {
    return age_on(84.016846);
}

double space_age::on_neptune() const {
    return age_on(164.79132);
}

}  // namespace space_age
