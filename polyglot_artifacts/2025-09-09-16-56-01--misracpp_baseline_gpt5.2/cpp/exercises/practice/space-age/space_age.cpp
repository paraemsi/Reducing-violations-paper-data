#include "space_age.h"

namespace {
constexpr double kEarthYearSeconds = 31557600.0;

constexpr double kMercuryOrbitalPeriod = 0.2408467;
constexpr double kVenusOrbitalPeriod   = 0.61519726;
constexpr double kEarthOrbitalPeriod   = 1.0;
constexpr double kMarsOrbitalPeriod    = 1.8808158;
constexpr double kJupiterOrbitalPeriod = 11.862615;
constexpr double kSaturnOrbitalPeriod  = 29.447498;
constexpr double kUranusOrbitalPeriod  = 84.016846;
constexpr double kNeptuneOrbitalPeriod = 164.79132;

inline double age_on(long long seconds, double orbital_period_in_earth_years) {
    return static_cast<double>(seconds) / (kEarthYearSeconds * orbital_period_in_earth_years);
}
}  // namespace

namespace space_age {

space_age::space_age(long long seconds) : seconds_(seconds) {}

long long space_age::seconds() const {
    return seconds_;
}

double space_age::on_earth() const {
    return age_on(seconds_, kEarthOrbitalPeriod);
}

double space_age::on_mercury() const {
    return age_on(seconds_, kMercuryOrbitalPeriod);
}

double space_age::on_venus() const {
    return age_on(seconds_, kVenusOrbitalPeriod);
}

double space_age::on_mars() const {
    return age_on(seconds_, kMarsOrbitalPeriod);
}

double space_age::on_jupiter() const {
    return age_on(seconds_, kJupiterOrbitalPeriod);
}

double space_age::on_saturn() const {
    return age_on(seconds_, kSaturnOrbitalPeriod);
}

double space_age::on_uranus() const {
    return age_on(seconds_, kUranusOrbitalPeriod);
}

double space_age::on_neptune() const {
    return age_on(seconds_, kNeptuneOrbitalPeriod);
}

}  // namespace space_age
