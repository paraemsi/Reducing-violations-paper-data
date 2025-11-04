#include "space_age.h"

namespace space_age {

namespace
{
    constexpr double kMercuryOrbitalPeriod { 0.2408467 };
    constexpr double kVenusOrbitalPeriod   { 0.61519726 };
    constexpr double kEarthOrbitalPeriod   { 1.0 };
    constexpr double kMarsOrbitalPeriod    { 1.8808158 };
    constexpr double kJupiterOrbitalPeriod { 11.862615 };
    constexpr double kSaturnOrbitalPeriod  { 29.447498 };
    constexpr double kUranusOrbitalPeriod  { 84.016846 };
    constexpr double kNeptuneOrbitalPeriod { 164.79132 };
    /* Seconds in one Earth year (365.25 days). */
    constexpr double kSecondsPerEarthYear { 31557600.0 };

    [[nodiscard]] static double age_on_planet(const std::int64_t seconds,
                                              const double       orbital_period)
    {
        /* Convert seconds to Earth years, then divide by the planet’s orbital period. */
        const double earth_years = static_cast<double>(seconds) /
                                   kSecondsPerEarthYear;

        return (earth_years / orbital_period);
    }
} // unnamed namespace

space_age::space_age(std::int64_t seconds) noexcept
    : seconds_{ seconds }
{
}

std::int64_t space_age::seconds(void) const noexcept
{
    return seconds_;
}

double space_age::on_earth(void) const noexcept
{
    return (age_on_planet(seconds_, kEarthOrbitalPeriod));
}

double space_age::on_mercury(void) const noexcept
{
    return (age_on_planet(seconds_, kMercuryOrbitalPeriod));
}

double space_age::on_venus(void) const noexcept
{
    return (age_on_planet(seconds_, kVenusOrbitalPeriod));
}

double space_age::on_mars(void) const noexcept
{
    return (age_on_planet(seconds_, kMarsOrbitalPeriod));
}

double space_age::on_jupiter(void) const noexcept
{
    return (age_on_planet(seconds_, kJupiterOrbitalPeriod));
}

double space_age::on_saturn(void) const noexcept
{
    return (age_on_planet(seconds_, kSaturnOrbitalPeriod));
}

double space_age::on_uranus(void) const noexcept
{
    return (age_on_planet(seconds_, kUranusOrbitalPeriod));
}

double space_age::on_neptune(void) const noexcept
{
    return (age_on_planet(seconds_, kNeptuneOrbitalPeriod));
}

}  // namespace space_age
