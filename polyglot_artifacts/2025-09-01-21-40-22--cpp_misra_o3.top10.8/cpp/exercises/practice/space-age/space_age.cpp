#include "space_age.h"

namespace
{
    /*  Seconds in an Earth year: 365.25 days × 24 h × 60 min × 60 s  */
    constexpr double seconds_per_earth_year { 31557600.0 };
} // unnamed namespace

namespace space_age {

space_age::space_age(std::uint64_t seconds) noexcept
    : m_seconds{ seconds }
{
    /* Constructor body intentionally left empty */
}

std::uint64_t space_age::seconds() const noexcept
{
    return m_seconds;
}

double space_age::age_on_planet(double orbital_ratio) const noexcept
{
    return (static_cast<double>(m_seconds) / seconds_per_earth_year) / orbital_ratio;
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
