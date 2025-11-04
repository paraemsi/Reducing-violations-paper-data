#include "space_age.h"

namespace {
    constexpr double kEarthYearSeconds = 31557600.0;  // 365.25 days
    constexpr double kMercury = 0.2408467;
    constexpr double kVenus   = 0.61519726;
    constexpr double kEarth   = 1.0;
    constexpr double kMars    = 1.8808158;
    constexpr double kJupiter = 11.862615;
    constexpr double kSaturn  = 29.447498;
    constexpr double kUranus  = 84.016846;
    constexpr double kNeptune = 164.79132;
}

namespace space_age {

space_age::space_age(long long seconds)
    : seconds_(seconds) {}

long long space_age::seconds() const {
    return seconds_;
}

double space_age::on_planet(double orbital_period) const {
    return static_cast<double>(seconds_) / (kEarthYearSeconds * orbital_period);
}

double space_age::on_earth() const {
    return on_planet(kEarth);
}

double space_age::on_mercury() const {
    return on_planet(kMercury);
}

double space_age::on_venus() const {
    return on_planet(kVenus);
}

double space_age::on_mars() const {
    return on_planet(kMars);
}

double space_age::on_jupiter() const {
    return on_planet(kJupiter);
}

double space_age::on_saturn() const {
    return on_planet(kSaturn);
}

double space_age::on_uranus() const {
    return on_planet(kUranus);
}

double space_age::on_neptune() const {
    return on_planet(kNeptune);
}

}  // namespace space_age
