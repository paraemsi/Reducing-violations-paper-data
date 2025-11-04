#include "space_age.h"

namespace space_age {

space_age::space_age(seconds_type seconds) noexcept
    : seconds_{seconds}
    , earth_years_{(static_cast<years_type>(seconds) / space_age::kEarthYearSeconds)}
{ }

seconds_type space_age::seconds() const noexcept
{
    return seconds_;
}


years_type space_age::on_earth() const noexcept
{
    return earth_years_;
}

years_type space_age::on_mercury() const noexcept
{
    constexpr double kOrbitalPeriod = 0.2408467;
    return (earth_years_ / kOrbitalPeriod);
}

years_type space_age::on_venus() const noexcept
{
    constexpr double kOrbitalPeriod = 0.61519726;
    return (earth_years_ / kOrbitalPeriod);
}

years_type space_age::on_mars() const noexcept
{
    constexpr double kOrbitalPeriod = 1.8808158;
    return (earth_years_ / kOrbitalPeriod);
}

years_type space_age::on_jupiter() const noexcept
{
    constexpr double kOrbitalPeriod = 11.862615;
    return (earth_years_ / kOrbitalPeriod);
}

years_type space_age::on_saturn() const noexcept
{
    constexpr double kOrbitalPeriod = 29.447498;
    return (earth_years_ / kOrbitalPeriod);
}

years_type space_age::on_uranus() const noexcept
{
    constexpr double kOrbitalPeriod = 84.016846;
    return (earth_years_ / kOrbitalPeriod);
}

years_type space_age::on_neptune() const noexcept
{
    constexpr double kOrbitalPeriod = 164.79132;
    return (earth_years_ / kOrbitalPeriod);
}

}  // namespace space_age
