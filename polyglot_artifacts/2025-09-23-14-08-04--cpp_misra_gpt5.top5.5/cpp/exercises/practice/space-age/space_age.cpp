#include "space_age.h"

namespace space_age {

namespace {
    constexpr double kEarthYearSeconds = 31557600.0;
    constexpr double kMercuryOrbitalPeriod = 0.2408467;
    constexpr double kVenusOrbitalPeriod = 0.61519726;
    constexpr double kEarthOrbitalPeriod = 1.0;
    constexpr double kMarsOrbitalPeriod = 1.8808158;
    constexpr double kJupiterOrbitalPeriod = 11.862615;
    constexpr double kSaturnOrbitalPeriod = 29.447498;
    constexpr double kUranusOrbitalPeriod = 84.016846;
    constexpr double kNeptuneOrbitalPeriod = 164.79132;

    constexpr double age_on_orbital_period(double seconds, double orbital_period) noexcept
    {
        const double year_seconds = (kEarthYearSeconds * orbital_period);
        return (seconds / year_seconds);
    }
}

space_age::space_age(double seconds) noexcept
    : seconds_(seconds)
{
}

double space_age::seconds() const noexcept
{
    return seconds_;
}

double space_age::on_earth() const noexcept
{
    return age_on_orbital_period(seconds_, kEarthOrbitalPeriod);
}

double space_age::on_mercury() const noexcept
{
    return age_on_orbital_period(seconds_, kMercuryOrbitalPeriod);
}

double space_age::on_venus() const noexcept
{
    return age_on_orbital_period(seconds_, kVenusOrbitalPeriod);
}

double space_age::on_mars() const noexcept
{
    return age_on_orbital_period(seconds_, kMarsOrbitalPeriod);
}

double space_age::on_jupiter() const noexcept
{
    return age_on_orbital_period(seconds_, kJupiterOrbitalPeriod);
}

double space_age::on_saturn() const noexcept
{
    return age_on_orbital_period(seconds_, kSaturnOrbitalPeriod);
}

double space_age::on_uranus() const noexcept
{
    return age_on_orbital_period(seconds_, kUranusOrbitalPeriod);
}

double space_age::on_neptune() const noexcept
{
    return age_on_orbital_period(seconds_, kNeptuneOrbitalPeriod);
}

}  // namespace space_age
