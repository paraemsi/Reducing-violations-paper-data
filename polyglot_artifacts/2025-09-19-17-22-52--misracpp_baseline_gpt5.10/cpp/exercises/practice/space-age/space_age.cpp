#include "space_age.h"

namespace {
constexpr double kEarthYearSeconds = 31557600.0;

constexpr double kMercuryOrbital = 0.2408467;
constexpr double kVenusOrbital   = 0.61519726;
constexpr double kEarthOrbital   = 1.0;
constexpr double kMarsOrbital    = 1.8808158;
constexpr double kJupiterOrbital = 11.862615;
constexpr double kSaturnOrbital  = 29.447498;
constexpr double kUranusOrbital  = 84.016846;
constexpr double kNeptuneOrbital = 164.79132;

inline double age_on(double seconds, double orbital_period) {
    return seconds / (kEarthYearSeconds * orbital_period);
}
}  // namespace

namespace space_age {

space_age::space_age(std::int64_t seconds) : seconds_{seconds} {}

std::int64_t space_age::seconds() const {
    return seconds_;
}

double space_age::on_earth() const {
    return age_on(static_cast<double>(seconds_), kEarthOrbital);
}

double space_age::on_mercury() const {
    return age_on(static_cast<double>(seconds_), kMercuryOrbital);
}

double space_age::on_venus() const {
    return age_on(static_cast<double>(seconds_), kVenusOrbital);
}

double space_age::on_mars() const {
    return age_on(static_cast<double>(seconds_), kMarsOrbital);
}

double space_age::on_jupiter() const {
    return age_on(static_cast<double>(seconds_), kJupiterOrbital);
}

double space_age::on_saturn() const {
    return age_on(static_cast<double>(seconds_), kSaturnOrbital);
}

double space_age::on_uranus() const {
    return age_on(static_cast<double>(seconds_), kUranusOrbital);
}

double space_age::on_neptune() const {
    return age_on(static_cast<double>(seconds_), kNeptuneOrbital);
}

}  // namespace space_age
