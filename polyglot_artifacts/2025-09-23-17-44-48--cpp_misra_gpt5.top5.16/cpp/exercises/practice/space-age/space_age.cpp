#include "space_age.h"

namespace {
    // Constants for orbital periods (in Earth years)
    constexpr double kSecondsPerEarthYear = 31557600.0;
    constexpr double kMercuryOrbitalPeriod = 0.2408467;
    constexpr double kVenusOrbitalPeriod   = 0.61519726;
    constexpr double kEarthOrbitalPeriod   = 1.0;
    constexpr double kMarsOrbitalPeriod    = 1.8808158;
    constexpr double kJupiterOrbitalPeriod = 11.862615;
    constexpr double kSaturnOrbitalPeriod  = 29.447498;
    constexpr double kUranusOrbitalPeriod  = 84.016846;
    constexpr double kNeptuneOrbitalPeriod = 164.79132;
}

namespace space_age {

space_age::space_age(std::uint64_t seconds) noexcept
    : seconds_(seconds) {
}

std::uint64_t space_age::seconds() const noexcept {
    return seconds_;
}

double space_age::on_earth() const noexcept {
    const double earth_years = (static_cast<double>(seconds_) / kSecondsPerEarthYear);
    return earth_years;
}

double space_age::on_mercury() const noexcept {
    const double earth_years = on_earth();
    return (earth_years / kMercuryOrbitalPeriod);
}

double space_age::on_venus() const noexcept {
    const double earth_years = on_earth();
    return (earth_years / kVenusOrbitalPeriod);
}

double space_age::on_mars() const noexcept {
    const double earth_years = on_earth();
    return (earth_years / kMarsOrbitalPeriod);
}

double space_age::on_jupiter() const noexcept {
    const double earth_years = on_earth();
    return (earth_years / kJupiterOrbitalPeriod);
}

double space_age::on_saturn() const noexcept {
    const double earth_years = on_earth();
    return (earth_years / kSaturnOrbitalPeriod);
}

double space_age::on_uranus() const noexcept {
    const double earth_years = on_earth();
    return (earth_years / kUranusOrbitalPeriod);
}

double space_age::on_neptune() const noexcept {
    const double earth_years = on_earth();
    return (earth_years / kNeptuneOrbitalPeriod);
}

}  // namespace space_age
