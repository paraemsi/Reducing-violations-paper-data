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

inline double on_planet(long long seconds, double orbital_period_in_earth_years) {
    return static_cast<double>(seconds) / (earth_year_seconds * orbital_period_in_earth_years);
}
}  // namespace

double space_age::on_earth() const { return on_planet(seconds_, earth_orbital); }
double space_age::on_mercury() const { return on_planet(seconds_, mercury_orbital); }
double space_age::on_venus() const { return on_planet(seconds_, venus_orbital); }
double space_age::on_mars() const { return on_planet(seconds_, mars_orbital); }
double space_age::on_jupiter() const { return on_planet(seconds_, jupiter_orbital); }
double space_age::on_saturn() const { return on_planet(seconds_, saturn_orbital); }
double space_age::on_uranus() const { return on_planet(seconds_, uranus_orbital); }
double space_age::on_neptune() const { return on_planet(seconds_, neptune_orbital); }

}  // namespace space_age
