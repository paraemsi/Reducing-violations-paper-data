#include "space_age.h"

namespace space_age {

namespace {
constexpr double kEarthYearSeconds = 31557600.0;
constexpr double kMercuryOrbital = 0.2408467;
constexpr double kVenusOrbital = 0.61519726;
constexpr double kMarsOrbital = 1.8808158;
constexpr double kJupiterOrbital = 11.862615;
constexpr double kSaturnOrbital = 29.447498;
constexpr double kUranusOrbital = 84.016846;
constexpr double kNeptuneOrbital = 164.79132;
}

space_age::space_age(long long seconds) : seconds_(seconds) {}

long long space_age::seconds() const {
    return seconds_;
}

double space_age::on_earth() const {
    return seconds_ / kEarthYearSeconds;
}

double space_age::on_mercury() const {
    return on_earth() / kMercuryOrbital;
}

double space_age::on_venus() const {
    return on_earth() / kVenusOrbital;
}

double space_age::on_mars() const {
    return on_earth() / kMarsOrbital;
}

double space_age::on_jupiter() const {
    return on_earth() / kJupiterOrbital;
}

double space_age::on_saturn() const {
    return on_earth() / kSaturnOrbital;
}

double space_age::on_uranus() const {
    return on_earth() / kUranusOrbital;
}

double space_age::on_neptune() const {
    return on_earth() / kNeptuneOrbital;
}

}  // namespace space_age
