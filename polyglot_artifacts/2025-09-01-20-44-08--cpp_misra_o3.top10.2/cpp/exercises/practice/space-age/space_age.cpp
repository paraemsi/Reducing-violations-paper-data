#include "space_age.h"

namespace space_age {

space_age::space_age(std::uint64_t seconds) noexcept
    : m_seconds{seconds}
{
}

std::uint64_t space_age::seconds() const noexcept
{
    return m_seconds;
}

double space_age::on_planet(double orbital_factor) const noexcept
{
    /*  Calculate the length of one year on the given planet in seconds.
        Keeping the intermediate result in a named variable improves readability
        and avoids relying on operator-precedence chains.  */
    const double planetary_year_seconds{(seconds_per_earth_year * orbital_factor)};

    /*  Age on the planet, expressed in that planet’s years.  */
    return (static_cast<double>(m_seconds) / planetary_year_seconds);
}

double space_age::on_earth() const noexcept
{
    return on_planet(1.0);
}

double space_age::on_mercury() const noexcept
{
    return on_planet(0.2408467);
}

double space_age::on_venus() const noexcept
{
    return on_planet(0.61519726);
}

double space_age::on_mars() const noexcept
{
    return on_planet(1.8808158);
}

double space_age::on_jupiter() const noexcept
{
    return on_planet(11.862615);
}

double space_age::on_saturn() const noexcept
{
    return on_planet(29.447498);
}

double space_age::on_uranus() const noexcept
{
    return on_planet(84.016846);
}

double space_age::on_neptune() const noexcept
{
    return on_planet(164.79132);
}

}  // namespace space_age
