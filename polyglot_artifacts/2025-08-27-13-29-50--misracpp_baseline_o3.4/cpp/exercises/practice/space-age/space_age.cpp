#include "space_age.h"

namespace {

constexpr double earth_year_seconds = 31557600.0;

constexpr double mercury_factor = 0.2408467;
constexpr double venus_factor   = 0.61519726;
constexpr double earth_factor   = 1.0;
constexpr double mars_factor    = 1.8808158;
constexpr double jupiter_factor = 11.862615;
constexpr double saturn_factor  = 29.447498;
constexpr double uranus_factor  = 84.016846;
constexpr double neptune_factor = 164.79132;

inline double age_in_years(std::int64_t seconds, double orbital_factor) {
    return seconds / (earth_year_seconds * orbital_factor);
}

} // namespace

namespace space_age {

space_age::space_age(std::int64_t seconds) : seconds_{seconds} {}

std::int64_t space_age::seconds() const {
    return seconds_;
}

double space_age::on_mercury() const {
    return age_in_years(seconds_, mercury_factor);
}

double space_age::on_venus() const {
    return age_in_years(seconds_, venus_factor);
}

double space_age::on_earth() const {
    return age_in_years(seconds_, earth_factor);
}

double space_age::on_mars() const {
    return age_in_years(seconds_, mars_factor);
}

double space_age::on_jupiter() const {
    return age_in_years(seconds_, jupiter_factor);
}

double space_age::on_saturn() const {
    return age_in_years(seconds_, saturn_factor);
}

double space_age::on_uranus() const {
    return age_in_years(seconds_, uranus_factor);
}

double space_age::on_neptune() const {
    return age_in_years(seconds_, neptune_factor);
}

}  // namespace space_age
