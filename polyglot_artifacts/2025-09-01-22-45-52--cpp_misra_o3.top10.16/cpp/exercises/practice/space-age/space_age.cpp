#include "space_age.h"

namespace space_age {


space_age::space_age(std::int64_t seconds) noexcept : seconds_{seconds}
{
}

std::int64_t space_age::seconds() const noexcept
{
    return seconds_;
}

double space_age::age_on_planet(double orbital_ratio) const noexcept
{
    /* Calculate age on a planet given its orbital ratio relative to Earth */
    return (static_cast<double>(seconds_) / space_age::earth_year_seconds_) / orbital_ratio;
}

double space_age::on_mercury() const noexcept
{
    return age_on_planet(0.2408467);
}

double space_age::on_venus() const noexcept
{
    return age_on_planet(0.61519726);
}

double space_age::on_earth() const noexcept
{
    return age_on_planet(1.0);
}

double space_age::on_mars() const noexcept
{
    return age_on_planet(1.8808158);
}

double space_age::on_jupiter() const noexcept
{
    return age_on_planet(11.862615);
}

double space_age::on_saturn() const noexcept
{
    return age_on_planet(29.447498);
}

double space_age::on_uranus() const noexcept
{
    return age_on_planet(84.016846);
}

double space_age::on_neptune() const noexcept
{
    return age_on_planet(164.79132);
}

}  // namespace space_age
