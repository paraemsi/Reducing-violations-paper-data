#include "space_age.h"

namespace space_age {

namespace {
constexpr double kEarthYearSeconds = 31557600.0;
constexpr double kMercury = 0.2408467;
constexpr double kVenus = 0.61519726;
constexpr double kEarth = 1.0;
constexpr double kMars = 1.8808158;
constexpr double kJupiter = 11.862615;
constexpr double kSaturn = 29.447498;
constexpr double kUranus = 84.016846;
constexpr double kNeptune = 164.79132;

inline double years_on(long long seconds, double orbital_period) {
    return static_cast<double>(seconds) / (kEarthYearSeconds * orbital_period);
}
}  // namespace

space_age::space_age(long long seconds) noexcept : seconds_{seconds} {}

long long space_age::seconds() const noexcept { return seconds_; }

double space_age::on_earth() const noexcept { return years_on(seconds_, kEarth); }
double space_age::on_mercury() const noexcept { return years_on(seconds_, kMercury); }
double space_age::on_venus() const noexcept { return years_on(seconds_, kVenus); }
double space_age::on_mars() const noexcept { return years_on(seconds_, kMars); }
double space_age::on_jupiter() const noexcept { return years_on(seconds_, kJupiter); }
double space_age::on_saturn() const noexcept { return years_on(seconds_, kSaturn); }
double space_age::on_uranus() const noexcept { return years_on(seconds_, kUranus); }
double space_age::on_neptune() const noexcept { return years_on(seconds_, kNeptune); }

}  // namespace space_age
