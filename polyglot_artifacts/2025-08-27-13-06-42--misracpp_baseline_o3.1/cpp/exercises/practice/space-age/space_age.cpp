#include "space_age.h"

namespace space_age {

// Definition of the static constexpr member declared in the header.
// This provides storage for the variable when compiling under C++14/C++11.
constexpr double space_age::earth_year_seconds_;

space_age::space_age(long long seconds) : seconds_{seconds} {}

long long space_age::seconds() const {
    return seconds_;
}

double space_age::on_earth() const {
    return convert(seconds_, 1.0);
}

double space_age::on_mercury() const {
    return convert(seconds_, 0.2408467);
}

double space_age::on_venus() const {
    return convert(seconds_, 0.61519726);
}

double space_age::on_mars() const {
    return convert(seconds_, 1.8808158);
}

double space_age::on_jupiter() const {
    return convert(seconds_, 11.862615);
}

double space_age::on_saturn() const {
    return convert(seconds_, 29.447498);
}

double space_age::on_uranus() const {
    return convert(seconds_, 84.016846);
}

double space_age::on_neptune() const {
    return convert(seconds_, 164.79132);
}

double space_age::convert(long long seconds, double orbital_period) {
    return seconds / (earth_year_seconds_ * orbital_period);
}

}  // namespace space_age
