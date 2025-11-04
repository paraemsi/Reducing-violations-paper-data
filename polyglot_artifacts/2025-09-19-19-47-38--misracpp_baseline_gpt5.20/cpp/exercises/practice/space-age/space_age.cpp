#include "space_age.h"

namespace space_age {

namespace {
    constexpr double earth_year_seconds = 31557600.0;

    constexpr double mercury_ratio = 0.2408467;
    constexpr double venus_ratio   = 0.61519726;
    constexpr double earth_ratio   = 1.0;
    constexpr double mars_ratio    = 1.8808158;
    constexpr double jupiter_ratio = 11.862615;
    constexpr double saturn_ratio  = 29.447498;
    constexpr double uranus_ratio  = 84.016846;
    constexpr double neptune_ratio = 164.79132;

    constexpr double to_years(long long seconds, double orbital_ratio) noexcept {
        return static_cast<double>(seconds) / (earth_year_seconds * orbital_ratio);
    }
}  // namespace

space_age::space_age(long long seconds) noexcept : seconds_{seconds} {}

long long space_age::seconds() const noexcept { return seconds_; }

double space_age::on_earth() const   noexcept { return to_years(seconds_, earth_ratio); }
double space_age::on_mercury() const noexcept { return to_years(seconds_, mercury_ratio); }
double space_age::on_venus() const   noexcept { return to_years(seconds_, venus_ratio); }
double space_age::on_mars() const    noexcept { return to_years(seconds_, mars_ratio); }
double space_age::on_jupiter() const noexcept { return to_years(seconds_, jupiter_ratio); }
double space_age::on_saturn() const  noexcept { return to_years(seconds_, saturn_ratio); }
double space_age::on_uranus() const  noexcept { return to_years(seconds_, uranus_ratio); }
double space_age::on_neptune() const noexcept { return to_years(seconds_, neptune_ratio); }

}  // namespace space_age
