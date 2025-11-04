#include "space_age.h"

namespace {
constexpr double earth_year_seconds = 31557600.0;
constexpr double mercury_period = 0.2408467;
constexpr double venus_period   = 0.61519726;
constexpr double earth_period   = 1.0;
constexpr double mars_period    = 1.8808158;
constexpr double jupiter_period = 11.862615;
constexpr double saturn_period  = 29.447498;
constexpr double uranus_period  = 84.016846;
constexpr double neptune_period = 164.79132;
}

namespace space_age {

space_age::space_age(long long seconds) : seconds_{seconds} {}

long long space_age::seconds() const { return seconds_; }

double space_age::on_earth() const { return seconds_ / earth_year_seconds / earth_period; }
double space_age::on_mercury() const { return seconds_ / earth_year_seconds / mercury_period; }
double space_age::on_venus() const { return seconds_ / earth_year_seconds / venus_period; }
double space_age::on_mars() const { return seconds_ / earth_year_seconds / mars_period; }
double space_age::on_jupiter() const { return seconds_ / earth_year_seconds / jupiter_period; }
double space_age::on_saturn() const { return seconds_ / earth_year_seconds / saturn_period; }
double space_age::on_uranus() const { return seconds_ / earth_year_seconds / uranus_period; }
double space_age::on_neptune() const { return seconds_ / earth_year_seconds / neptune_period; }

}  // namespace space_age
