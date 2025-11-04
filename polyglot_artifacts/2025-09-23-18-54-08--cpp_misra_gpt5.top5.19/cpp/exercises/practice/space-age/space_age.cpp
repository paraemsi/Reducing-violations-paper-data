#include "space_age.h"

namespace space_age {

space_age::space_age(std::uint64_t seconds) noexcept
    : seconds_{seconds} {
}

std::uint64_t space_age::seconds() const noexcept {
    return seconds_;
}

double space_age::on_planet(const double orbital_period_in_earth_years) const noexcept {
    const double seconds_as_double = static_cast<double>(seconds_);
    const double denominator = (kEarthYearSeconds * orbital_period_in_earth_years);
    return (seconds_as_double / denominator);
}

double space_age::on_earth() const noexcept {
    return on_planet(kEarthOrbitalPeriod);
}

double space_age::on_mercury() const noexcept {
    return on_planet(kMercuryOrbitalPeriod);
}

double space_age::on_venus() const noexcept {
    return on_planet(kVenusOrbitalPeriod);
}

double space_age::on_mars() const noexcept {
    return on_planet(kMarsOrbitalPeriod);
}

double space_age::on_jupiter() const noexcept {
    return on_planet(kJupiterOrbitalPeriod);
}

double space_age::on_saturn() const noexcept {
    return on_planet(kSaturnOrbitalPeriod);
}

double space_age::on_uranus() const noexcept {
    return on_planet(kUranusOrbitalPeriod);
}

double space_age::on_neptune() const noexcept {
    return on_planet(kNeptuneOrbitalPeriod);
}

}  // namespace space_age
